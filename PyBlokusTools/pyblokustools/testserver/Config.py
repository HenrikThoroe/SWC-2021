from __future__ import annotations

import os
from pathlib import Path
from json import load, dump

class Config():
    """TestServer Config to save values between runs

    Arguments:
        serverPath    {str} -- Path to current SWC Server                        (default: "")
        serverVersion {str} -- Current SWC Server version                        (default: "")
        serverHash    {str} -- Hash of current Server zip as from the Github API (default: "")
    """
    def __init__(self, serverPath: str = "", serverVersion: str = "", serverHash: str = "", **kwargs) -> None:
        self.serverPath    = serverPath or Path(f'{os.path.dirname(os.path.realpath(__file__))}/data/server.zip').resolve().as_posix()
        self.serverVersion = serverVersion
        self.serverHash    = serverHash
        
        self.usable        = serverPath != "" and serverVersion != "" and serverHash != ""
    
    @staticmethod
    def load() -> Config:
        """Try to load a config from disk, construct new one on failure

        Returns:
            Config -- Config to use for this run
        """
        ownDir = os.path.dirname(os.path.realpath(__file__))
        
        path = Path(f'{ownDir}/data/config.json')
        if path.is_file():
            try:
                with open(path.resolve(), 'r') as file:
                    return Config(**load(file))
            except:
                return Config()
        else:
            #? Create new empty config
            return Config()
    
    def save(self) -> None:
        """Save current config to disk
        """
        ownDir = os.path.dirname(os.path.realpath(__file__))
        
        path = Path(f'{ownDir}/data/config.json')
        
        with open(path.resolve(), 'w') as file:
            dump(self.__dict__, file)
