from typing import Optional, Callable, Tuple, List

from subprocess import Popen, PIPE, STDOUT
from time import time, sleep # Remove sleep once the server is fixed
import logging

from .TCPClient import TCPClient
from .XMLParser import XMLParser
from .Logger import Logger
from .Message import *

class GameManager():
    """Main GameManager for playing actual games

    Arguments:
        serverClient      {TCPClient}                   -- TCPClient already connected and authenticated
        serverPort        {int}                         -- Port the clients should connect to
        clients           {Tuple[str, str]}             -- Paths to the two clients to test
        clientNames       {Tuple[str, str]}             -- Names for the two clients
        clientArguments   {Tuple[List[str], List[str]]} -- Arguments to start clients with
        clientsCanTimeout {Tuple[bool, bool]}           -- If clients can timeout
        logger            {Logger}                      -- Logger to save clientLogs to
        tcpFactory        {Callable[[], TCPClient]}     -- A factory function for a connected TCPClient
    """
    def __init__(
        self,
        serverClient      : TCPClient,
        serverPort        : int,
        clients           : Tuple[str, str],
        clientNames       : Tuple[str, str],
        clientArguments   : Tuple[List[str], List[str]],
        clientsCanTimeout : Tuple[bool, bool],
        logger            : Logger,
        tcpFactory        : Callable[[], TCPClient],
    ) -> None:
        self.serverClient      = serverClient
        self.serverPort        = str(serverPort)
        self.clients           = clients
        self.clientNames       = clientNames
        self.clientArguments   = clientArguments
        self.clientsCanTimeout = [str(x).lower() for x in clientsCanTimeout]
        self.logger            = logger
        self.tcpFactory        = tcpFactory
        
        self._l                = logging.getLogger("TestServer.GameManager")
        
        self.playedGames       = 0 # Number of games already played (to switch client colors)
        self.kill: Callable[[], None] = lambda: None
    
    def run(self) -> Optional[ResultMsg]:
        """Play one game with both clients

        Returns:
            Optional[ResultMsg] -- Results of the game played on success, None otherwise
        """
        self._resetState()
        
        player1 = self.playedGames       % 2
        player2 = (self.playedGames + 1) % 2
        self.playedGames += 1
        
        reservations = self._prepareGame(player1=player1, player2=player2)
        
        # Start clients
        client1 = Popen([self.clients[player1], '-p', self.serverPort, '-r', reservations[0], *self.clientArguments[player1]], stdout=PIPE, stderr=STDOUT)
        client2 = Popen([self.clients[player2], '-p', self.serverPort, '-r', reservations[1], *self.clientArguments[player2]], stdout=PIPE, stderr=STDOUT)
        
        def kill() -> None:
            """Kill all running clients
            """
            try:
                client1.kill()
                client1.wait()
            except:
                pass
            try:
                client2.kill()
                client2.wait()
            except:
                pass
        
        self.kill = kill
        
        #? These are commented out as per 
        # sleep(0.5) # See Bugreport on Discord -> Server is overwhelmed lmao
        # self.serverClient.send(f'<pause roomId="{self._roomId}" pause="false" />') # Start game
        
        started = False
        timer   = int(time())
        # Handle server messages
        while True:
            messages: List[Message] = []
            if inp := self.serverClient.receive():
                started = True # Deactivate redeemed reservations test
                timer   = int(time()) # Reset timer to detect timeouts
                XMLParser.splitAndParseMessages(inp, messages)
                
                for msg in messages:
                    if msg.type == MsgType.GAMESTATE:
                        self._turn = msg.payload.currentTurn
                    elif msg.type == MsgType.RESULT:
                        
                        # Wait for clients to shutdown
                        try:
                            client1.wait(5)
                        except:
                            self._l.error(f"Client did not shutdown after 5sec: '{self.clientNames[player1]}'")
                            client1.kill()
                            client1.wait()
                        try:
                            client2.wait(5)
                        except:
                            self._l.error(f"Client did not shutdown after 5sec: '{self.clientNames[player2]}'")
                            client2.kill()
                            client2.wait()
                        
                        # Save client logs
                        self.logger.logClient(player1, client1.stdout)
                        self.logger.logClient(player2, client2.stdout)
                        
                        # Swap player scores as we swaped their reservations (normalise)
                        if player1 != 0:
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
                        self._l.error(f"Client crashed in game {self.playedGames - 1}")

                messages.clear()
            else:
                if not started and (time() - timer) > 25:
                    #? Game didnt start? -> Try out both gameCodes to see which client failed to connect
                    rTCPClient1, rTCPClient2 = self.tcpFactory(), self.tcpFactory()
                    
                    rTCPClient1.send(f'<joinPrepared reservationCode="{reservations[0]}" />')
                    rTCPClient2.send(f'<joinPrepared reservationCode="{reservations[1]}" />')
                    
                    inp1 = rTCPClient1.receive()
                    inp2 = rTCPClient2.receive()
                    
                    if inp1 == False or inp2 == False:
                        self._l.critical("Could not test redeemed reservations")
                        return None
                    
                    messages1: List[Message] = []
                    messages2: List[Message] = []
                    
                    XMLParser.splitAndParseMessages(inp1, messages1)
                    XMLParser.splitAndParseMessages(inp2, messages2)
                    
                    if not any([msg.type == MsgType.CLOSECONN for msg in messages1]):
                        self._l.error(f"Client '{self.clientNames[player1]}' did not redeem its reservation")
                    if not any([msg.type == MsgType.CLOSECONN for msg in messages2]):
                        self._l.error(f"Client '{self.clientNames[player2]}' did not redeem its reservation")
                    
                    return None
                elif (time() - timer) > 60:
                    raise RuntimeWarning("Did not recieve any message from the server for 60sec")
    
    def _resetState(self) -> None:
        """Reset own state before running new game
        """
        # Clear Server Messages
        while self.serverClient.receive():
            pass
        self.serverClient._buffer        = b''
        self.serverClient._decodedBuffer = ""
        
        # Clear internal state
        self._roomId = ""
        self._turn   = 0
    
    def _prepareGame(self, player1: int, player2: int) -> Tuple[str, str]:
        """Prepare a new game
        
        Arguments:
            player1 {int} -- Index of first player
            player2 {int} -- Index of second player

        Returns:
            Tuple[str] -- Reservation codes for the clients
        """
        messages: List[Message] = []
        
        client1, canTimeout1 = self.clientNames[player1], self.clientsCanTimeout[player1]
        client2, canTimeout2 = self.clientNames[player2], self.clientsCanTimeout[player2]
        
        #? Create new game
        # Request
        self.serverClient.send(f'<prepare gameType="swc_2021_blokus" pause="false"><slot displayName="{client1}" canTimeout="{canTimeout1}" /><slot displayName="{client2}" canTimeout="{canTimeout2}" /></prepare>')
        
        # Handling response
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
