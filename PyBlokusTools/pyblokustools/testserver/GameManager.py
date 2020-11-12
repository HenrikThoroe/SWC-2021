from typing import Any, Final, Tuple, List

from subprocess import Popen, PIPE, STDOUT
import time # Remove once the server is fixed

from .TCPClient import TCPClient
from .XMLParser import XMLParser
from .Message import *

class GameManager():
    """Main GameManager for playing actual games

    Arguments:
        serverClient    {TCPClient}        -- TCPClient already connected and authenticated
        clients         {Tuple[str, str]}       -- Paths to the two clients to test
        clientNames     {Tuple[str, str]}       -- Names for the two clients
        clientArguments {Tuple[List[str], List[str]]} -- Arguments to start clients with
    """
    def __init__(self, serverClient: TCPClient, clients: Tuple[str, str], clientNames: Tuple[str, str], clientArguments: Tuple[List[str], List[str]]) -> None:
        self.serverClient    = serverClient
        self.clients         = clients
        self.clientNames     = clientNames
        self.clientArguments = clientArguments
        self.playedGames     = 0 # Number of games already played (to switch client colors)
    
    def run(self) -> ResultMsg:
        """Play one game with both clients

        Returns:
            ResultMsg -- Results of the game played
        """
        self._resetState()
        
        reservations = self._prepareGame()
        
        # Start clients
        client1 = Popen([self.clients[0], '-r', reservations[0] if self.playedGames % 2 == 0 else reservations[1], *self.clientArguments[0]], stdout=PIPE, stderr=STDOUT)
        client2 = Popen([self.clients[1], '-r', reservations[1] if self.playedGames % 2 == 0 else reservations[0], *self.clientArguments[1]], stdout=PIPE, stderr=STDOUT)
        
        time.sleep(0.5) # See Bugreport on Discord -> Server is overwhelmed lmao
        self.serverClient.send(f'<pause roomId="{self._roomId}" pause="false" />') # Start game
        
        # Handle server messages
        while True:
            messages: List[Message] = []
            if inp := self.serverClient.receive():
                XMLParser.splitAndParseMessages(inp, messages)
                
                for msg in messages:
                    if msg.type == MsgType.GAMESTATE:
                        self._turn = msg.payload.currentTurn
                    elif msg.type == MsgType.RESULT:
                        # Wait for clients to shutdown
                        try:
                            client1.wait(5)
                        except:
                            raise RuntimeError(f"Client did not shutdown after 5sec: '{self.clientNames[0]}'")
                        try:
                            client2.wait(5)
                        except:
                            raise RuntimeError(f"Client did not shutdown after 5sec: '{self.clientNames[1]}'")
                        
                        return msg.payload
        
    def _resetState(self) -> None:
        """Reset own state before running new game
        """
        self._roomId = ""
        self._turn   = 0
    
    def _prepareGame(self) -> Tuple[str, str]:
        """Prepare a new game

        Returns:
            Tuple[str] -- Reservation codes for the clients
        """
        #? Create new game
        # Request
        client1 = self.clientNames[self.playedGames   % 2]
        client2 = self.clientNames[self.playedGames+1 % 2]
        self.serverClient.send(f'<prepare gameType="swc_2021_blokus"><slot displayName="{client1}" canTimeout="true" shouldBePaused="true" /><slot displayName="{client2}" canTimeout="true" shouldBePaused="true" /></prepare>')
        
        # Handling response
        messages: List[Message] = []
        inp = self.serverClient.receive()
        if inp == False:
            raise ValueError("Did not recieve 'prepared' message from the server")
        
        XMLParser.splitAndParseMessages(inp, messages)
        
        if len(messages) != 1 or messages[0].type != MsgType.PREPARED:
            raise ValueError(f"Recieved invalid amount of messages, expected only 'prepared' message: {messages}")
        
        prepMsg = messages[0]
        self._roomId = prepMsg.payload.roomId
        
        #? Observe game
        # Request
        self.serverClient.send(f'<observe roomId="{self._roomId}" />')
        
        return prepMsg.payload.reservations
