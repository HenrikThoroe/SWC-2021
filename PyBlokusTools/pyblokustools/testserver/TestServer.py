from typing import Optional, Callable, Tuple, List

import os
import atexit
import tempfile
import zipfile
import logging
import signal
from time import sleep, time
from functools import wraps
from datetime import timedelta
from subprocess import Popen, PIPE, STDOUT
from tqdm import tqdm, trange # type: ignore
from requests import get

from .Config import Config
from .Logger import Logger
from .TCPClient import TCPClient
from .GameManager import GameManager

class TestServer():
    """High level interface for the TestServer

    Arguments:
        clients           {Tuple[str, str]}             -- Paths to the two clients to test
        clientNames       {Tuple[str, str]}             -- Names for the two clients
        clientArguments   {Tuple[List[str], List[str]]} -- Arguments to start clients with
        clientsCanTimeout {Tuple[bool, bool]}           -- If clients can timeout           (default: [True, True])
        serverPort        {int}                         -- Port the server should run on    (default: 13055)
        logEnabled        {bool}                        -- Logging enabled                  (default: True)
        logLevel          {int}                         -- Log level to use                 (default: logging.INFO)
        jsonLogs          {bool}                        -- Special JSONLogs enabled         (default: False)
    """
    def __init__(
        self,
        clients           : Tuple[str, str],
        clientNames       : Tuple[str, str],
        clientArguments   : Tuple[List[str], List[str]],
        clientsCanTimeout : Tuple[bool, bool]            = [True, True],
        serverPort        : int                          = 13055,
        logEnabled        : bool                         = True,
        logLevel          : int                          = logging.INFO,
        jsonLogs          : bool                         = False,
    ) -> None:
        self.clients          = clients
        self.clientNames      = clientNames
        self.clientArguments  = clientArguments
        self.clientsCanTimeout = clientsCanTimeout
        self.serverPort       = serverPort
        self.jsonLogs         = jsonLogs
        
        self.config = Config.load()
        
        self.logger = Logger(
            clientNames = clientNames,
            enabled     = logEnabled,
            level       = logLevel,
            )
        logging.basicConfig(format='%(asctime)s %(levelname)s  %(message)s', datefmt='%H:%M:%S', level=logLevel)
        self._l = logging.getLogger("TestServer")
        self._l.propagate = False
        self._l.addHandler(self.logger)
        
        self.serverPath = self._fetchServer()
        
        self.serverProc: Popen
        self.client, tcpFactory = self._startServer()
        
        self.manager = GameManager(
            serverClient      = self.client,
            serverPort        = self.serverPort,
            clients           = clients,
            clientNames       = clientNames,
            clientArguments   = clientArguments,
            clientsCanTimeout = clientsCanTimeout,
            logger            = self.logger,
            tcpFactory        = tcpFactory,
            )
        
        self.scores = [0, 0] # 0: Lose, 1: Draw, 2: Win
        self.points = [0, 0] # Summ of all in game points
        self.failedGames = 0
        
        self.config.save()
    
    def _fetchServer(self) -> str:
        """Fetch the newest version of the SWC Server from github

        Returns:
            str -- Path to server
        """
        def fallback() -> str:
            """Try to fallback to version on disk

            Returns:
                str -- Path to server
            """
            self._l.warning("Could not fetch newest SWC Server version from Github")
            
            if not self.config.usable:
                self._l.critical("No fallback for SWC Server found, exiting")
                raise SystemExit()
            
            self._l.info(f"Falling back to server version {self.config.serverVersion} from disk")
            return self.config.serverPath
        
        self._l.info("Fetching newest SWC Server version from Github...")
        
        try:
            releases = get("https://api.github.com/repos/CAU-Kiel-Tech-Inf/backend/releases", params={'per_page': 1})
        except:
            #? No internet connection
            self._l.warning("Could not reach Github")
            return fallback()
        
        if releases.status_code != 200:
            #? Other error
            self._l.warning(f"Got response with status code '{releases.status_code}'")
            return fallback()

        j = releases.json()[0]
        tag_name = j['tag_name']
        assets   = j['assets'] # Most current versions assets
        
        for asset in assets:
            if asset['name'] == "software-challenge-server.zip":
                if asset['node_id'] != self.config.serverHash:
                    #? Found newer asset, now download new version
                    url = asset['browser_download_url']
                    
                    try:
                        with tempfile.TemporaryFile() as file:
                            file.write(get(url, allow_redirects=True).content)
                            file.seek(0)
                            
                            with zipfile.ZipFile(file, 'r') as serverZip:
                                serverZip.extractall(os.path.dirname(self.config.serverPath))
                            
                            self.config.serverHash    = asset['node_id']
                            self.config.serverVersion = tag_name 
                            
                            self._l.info(f"Using freshly downloaded server version {tag_name}")
                            return self.config.serverPath
                    except:
                        self._l.warning(f"Could not download server verion {tag_name}")
                        return fallback()

                self._l.info(f"Using current server version {self.config.serverVersion} from disk")
                return self.config.serverPath
                
        self._l.error("Did not find 'software-challenge-server.zip' in assets")
        return fallback()

    def _startServer(self) -> Tuple[TCPClient, Callable[[], TCPClient]]:
        """Start the SWC Server and establish a connection to it

        Returns:
            TCPClient               -- Connected and authenticated client
            Callable[[], TCPClient] -- Factory function to create new connected TCPClients
        """
        self.serverProc = Popen(
            ['sh', self.config.serverPath, '-p', str(self.serverPort)],
            stdout     = PIPE,
            stderr     = STDOUT,
            cwd        = os.path.dirname(self.config.serverPath),
            preexec_fn = os.setsid,
            )
        
        def killSWCServer() -> None:
            """Called before termination of TestServer to make sure the SWC server is shut down
            """
            os.killpg(os.getpgid(self.serverProc.pid), signal.SIGTERM)
            self.serverProc.kill()
            self.serverProc.wait()
        
        atexit.register(killSWCServer)
        
        os.set_blocking(self.serverProc.stdout.fileno(), False) # type: ignore
        
        self._l.info("Booting up SWC server...")
        sleep(5)
        
        def tcpFactory() -> TCPClient:
            """Create a connected TCPClient instance

            Returns:
                TCPClient -- Client connected to the SWC server
            """
            return TCPClient("localhost", self.serverPort)
        
        client = tcpFactory()
        client.send('<authenticate password="examplepassword" />')
        
        self._l.info(f"SWC server started on port '{self.serverPort}'")        
        return client, tcpFactory
    
    def run(self, *, iterations: Optional[int] = None, deltatime: Optional[timedelta] = None) -> None:
        """Run configured mass tests (specify either iterations or time)

        Keyword Arguments:
            iterations {Optional[int]}       -- Test runs to execute (default: {None})
            deltatime  {Optional[timedelta]} -- Time to test for     (default: {None})

        Raises:
            TypeError: Invalid arguments
        """
        if iterations is None and deltatime is None:
            raise TypeError("Please specify iterations or deltatime")
        
        #? Define decorator
        if isinstance(iterations, int) and iterations > 0:
            def _(func: Callable[[], None]) -> Callable[[], None]:
                """Decorator to execute func x times

                Arguments:
                    func {Callable[[], None]} -- Function to repeat
                
                Returns:
                    Callable[[], None] -- Repeated function
                """
                @wraps(func)
                def f(*args, **kwargs) -> None:
                    with trange(iterations, unit="Game") as t:
                        t.set_postfix_str(f"Scores {self.scores[0]}:{self.scores[1]}")
                        for run in t:
                            t.set_description(f'Game {self.manager.playedGames+1}')
                            func()
                            t.set_postfix_str(f"Scores {self.scores[0]}:{self.scores[1]}")
                return f            
        elif isinstance(deltatime, timedelta) and deltatime.total_seconds() > 0:
            def _(func: Callable[[], None]) -> Callable[[], None]:
                """Decorator to execute func for a specific time

                Arguments:
                    func {Callable[[], None]} -- Function to repeat
                
                Returns:
                    Callable[[], None] -- Repeated function
                """
                @wraps(func)
                def f(*args, **kwargs) -> None:
                    left    = int(deltatime.total_seconds()) # type: ignore
                    elapsed = 0
                    elapsedMean = 0
                    
                    with tqdm(iterations, unit="Game", total=left, bar_format="{desc} {percentage:3.0f}%|{bar}| {n_fmt}/{total_fmt} [{elapsed}<{remaining} {postfix}]") as t:
                        while left > elapsed:
                            t.set_postfix_str(f"{str(round(elapsedMean / self.manager.playedGames, 1))+'s' if self.manager.playedGames > 0 else '?'}/Game , Scores {self.scores[0]}:{self.scores[1]}")
                            t.set_description(f'Game {self.manager.playedGames+1}')
                            
                            left -= elapsed
                            
                            t.update(elapsed)
                            
                            e1 = time()
                            func()
                            _ = time()-e1
                            elapsedMean += _
                            elapsed = int(_)
                            
                        t.update(left)
                        t.set_postfix_str(f"{str(round(elapsedMean / self.manager.playedGames, 1))+'s' if self.manager.playedGames > 0 else '?'}/Game , Scores {self.scores[0]}:{self.scores[1]}")
                        
                return f
        else:
            raise TypeError("Neither iterations nor time have a valid value")
        
        #? Run repeated tests
        @_
        def _run() -> None:
            """Function that actually runs the mass tests
            """
            # Prepare logger for new game
            self.logger.makeDirs()
            
            # Run actual game
            try:
                result = self.manager.run()
                sleep(2) # Wait for server logs to populate
                
                if not result:
                    #? Game failed
                    self.manager.kill()
                    self.failedGames += 1
                    sleep(2) # Wait for server logs to populate
                    
                    self.logger.logFile(f"Could not finish Game {self.manager.playedGames}:\n\tScore is now: {self.clientNames[0]}: {self.scores[0]}, {self.clientNames[1]}: {self.scores[1]}\n")
                    
                    # Write Serverlogs to current game logs
                    self.logger.logServer(self.serverProc.stdout)
                    return
            except Exception as e:
                #? Game crashed
                self.manager.kill()
                self.failedGames += 1
                sleep(2) # Wait for server logs to populate
                
                self._l.critical(f"Fatal error during game {self.manager.playedGames}?", exc_info=True)
                # Write Serverlogs to current game logs
                self.logger.logServer(self.serverProc.stdout)
                return
                            
            # Update scores, points and log them
            self.scores[0] += int(result.end[0])
            self.scores[1] += int(result.end[1])
            self.points[0] += int(result.score[0])
            self.points[1] += int(result.score[1])
            self.logger.logFile(f"Finished Game {self.manager.playedGames}:\n\t{result.__repr__()}\n\tScore is now: {self.clientNames[0]}: {self.scores[0]}, {self.clientNames[1]}: {self.scores[1]}\n")
            
            self._l.debug(f"Finished game {self.manager.playedGames} - {result.end[0]}:{result.end[1]}")
            
            # Write Serverlogs to current game logs
            self.logger.logServer(self.serverProc.stdout)
        
        self._l.info("Running MassTests...")
        _run()
        self.logger.logFile(f"\n\nFinal Scores {self.clientNames[0]}: {self.scores[0]}, {self.clientNames[1]}: {self.scores[1]}\nFinal Points {self.clientNames[0]}: {self.points[0]}, {self.clientNames[1]}: {self.points[1]}\nAfter {self.manager.playedGames} games ({self.failedGames} failed)")

        if self.jsonLogs:
            #? Special JSONLogs for automated analysis
            self.logger.logJSONFile(
                {
                    'games'   : self.manager.playedGames,
                    'failed'  : self.failedGames,
                    'clients' : {
                        self.clientNames[0] : {
                            'score'  : self.scores[0],
                            'points' : self.points[0],
                        },
                        self.clientNames[1] : {
                            'score'  : self.scores[1],
                            'points' : self.points[1],
                        },
                    },
                }
            )
