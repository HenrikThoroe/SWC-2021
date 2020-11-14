from typing import Optional, Tuple, List

import tempfile
import zipfile
import logging
from tqdm import tqdm # type: ignore
from requests import get

from .Config import Config
from .Logger import Logger
from .GameManager import GameManager

class TestServer():
    """High level interface for the TestServer

    Arguments:
        clients         {Tuple[str, str]}             -- Paths to the two clients to test
        clientNames     {Tuple[str, str]}             -- Names for the two clients
        clientArguments {Tuple[List[str], List[str]]} -- Arguments to start clients with
        logEnabled      {bool}                        -- Logging enabled
        logLevel        {int}                         -- Log level to use (default: logging.INFO)
    """
    def __init__(self, clients: Tuple[str, str], clientNames: Tuple[str, str], clientArguments: Tuple[List[str], List[str]], logEnabled: bool = True, logLevel: int = logging.INFO) -> None:
        self.clients         = clients
        self.clientNames     = clientNames
        self.clientArguments = clientArguments
        
        self.config = Config.load()
        
        self.manager = GameManager(
            serverClient    = self._fetchServer(),
            clients         = clients,
            clientNames     = clientNames,
            clientArguments = clientArguments,
            )
        self.logger = Logger(
            clientNames = clientNames,
            enabled     = logEnabled,
            level       = logLevel,
            )
        
        logging.basicConfig(format='%(asctime)s %(levelname)s  %(message)s', datefmt='%H:%M:%S', level=logLevel)
        self._l = logging.getLogger("TestServer")
        self._l.addHandler(self.logger)
    
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
            
            if not config.usable:
                self._l.critical("No fallback for SWC Server found, exiting")
                raise SystemExit()
            
            return config.serverPath
        
        self._l.info("Fetching newest SWC Server version from Github...")
        
        try:
            releases = get("https://api.github.com/repos/CAU-Kiel-Tech-Inf/backend/releases", params={'per_page': 1})
        except:
            #? No internet connection
            self._l.warning("Could not reach Github")
            return fallback()
        
        if r.status_code != 200:
            #? Other error
            self._l.warning(f"Got response with status code '{r.status_code}'")
            return fallback()

        j = r.json()[0]
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
                            
                            self._l.info(f"Using freshly downloaded server version {tag_name}")
                            return self.config.serverPath
                    except:
                        self._l.warning(f"Could not download server verion {tag_name}")
                        return fallback()

                self._l.info(f"Using current version server version {self.config.version} from disk")
                return self.config.serverPath
                
        self._l.exception("Did not find 'software-challenge-server.zip' in assets")
        return fallback()
                
        
