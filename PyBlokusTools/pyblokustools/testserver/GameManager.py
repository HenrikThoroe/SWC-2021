from typing import Any, Final, Tuple, List

from subprocess import Popen, PIPE, STDOUT
import time # Remove once the server is fixed
import logging

from .TCPClient import TCPClient
from .XMLParser import XMLParser
from .Logger import Logger
from .Message import *

class GameManager():
    """Main GameManager for playing actual games

    Arguments:
        serverClient    {TCPClient}                   -- TCPClient already connected and authenticated
        serverPort      {int}                         -- Port the clients should connect to
        clients         {Tuple[str, str]}             -- Paths to the two clients to test
        clientNames     {Tuple[str, str]}             -- Names for the two clients
        clientArguments {Tuple[List[str], List[str]]} -- Arguments to start clients with
    """
    def __init__(self, serverClient: TCPClient, serverPort: int, clients: Tuple[str, str], clientNames: Tuple[str, str], clientArguments: Tuple[List[str], List[str]], logger: Logger) -> None:
        self.serverClient    = serverClient
        self.serverPort      = str(serverPort)
        self.clients         = clients
        self.clientNames     = clientNames
        self.clientArguments = clientArguments
        self.logger          = logger
        
        self._l              = logging.getLogger("TestServer.GameManager")
        
        self.playedGames     = 0 # Number of games already played (to switch client colors)
    
    def run(self) -> ResultMsg:
        """Play one game with both clients

        Returns:
            ResultMsg -- Results of the game played
        """
        self._resetState()
        
        reservations = self._prepareGame()
        
        # Start clients
        client1 = Popen([self.clients[0], '-p', self.serverPort, '-r', reservations[0] if self.playedGames % 2 == 0 else reservations[1], *self.clientArguments[0]], stdout=PIPE, stderr=STDOUT)
        client2 = Popen([self.clients[1], '-p', self.serverPort, '-r', reservations[1] if self.playedGames % 2 == 0 else reservations[0], *self.clientArguments[1]], stdout=PIPE, stderr=STDOUT)
        
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
                        self.playedGames += 1
                        
                        # Wait for clients to shutdown
                        try:
                            client1.wait(5)
                        except:
                            self._l.error(f"Client did not shutdown after 5sec: '{self.clientNames[0]}'")
                            client1.kill()
                            client1.wait()
                        try:
                            client2.wait(5)
                        except:
                            self._l.error(f"Client did not shutdown after 5sec: '{self.clientNames[1]}'")
                            client2.kill()
                            client2.wait()
                        
                        # Save client logs
                        self.logger.logClient(0, client1.stdout)
                        self.logger.logClient(1, client2.stdout)
                        
                        # Swap player scores as we swaped their reservations
                        # (== 0 here because we already incremented self.playedGames at the top of this if)
                        if self.playedGames % 2 == 0:
                            msg.payload.swap()
                        
                        # Check ending reason
                        def checkEnd(cause: ResultCause, client: int) -> None:
                            """Checks the game ending cause for both players

                            Arguments:
                                cause  {ResultCause} -- Cause of game ending
                                client {int}         -- Client id of this cause
                            """
                            if cause == ResultCause.REGULAR:
                                self._l.debug(f"Client {self.clientNames[client]} ended REGULAR")
                            if cause == ResultCause.LEFT:
                                self._l.error(f"Client {self.clientNames[client]} LEFT the game")
                            if cause == ResultCause.RULE_VIOLATION:
                                self._l.critical(f"Client {self.clientNames[client]} VIOLATED the RULES")
                            if cause == ResultCause.SOFT_TIMEOUT:
                                self._l.error(f"Client {self.clientNames[client]} SOFT TIMEOUTED")
                            if cause == ResultCause.HARD_TIMEOUT:
                                self._l.error(f"Client {self.clientNames[client]} HARD TIMEOUTED")
                        
                        checkEnd(msg.payload.cause[0], 0)
                        checkEnd(msg.payload.cause[1], 1)
                        
                        return msg.payload
                    elif msg.type == MsgType.LEFT:
                        self._l.error(f"Client crashed in game {self.playedGames}")
        
    def _resetState(self) -> None:
        """Reset own state before running new game
        """
        # Clear Server Messages
        while self.serverClient.receive():
            pass
        self.serverClient._buffer = ""
        
        # Clear internal state
        self._roomId = ""
        self._turn   = 0
    
    def _prepareGame(self) -> Tuple[str, str]:
        """Prepare a new game

        Returns:
            Tuple[str] -- Reservation codes for the clients
        """
        #? Create new game
        # Request
        client1 = self.clientNames[self.playedGames     % 2]
        client2 = self.clientNames[(self.playedGames+1) % 2]
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
