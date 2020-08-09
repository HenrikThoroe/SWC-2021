from typing import Union, List

import hashlib
import json

class Hasher():
    BUF_SIZE = 65536
    
    @staticmethod
    def hashFile(filePath: str) -> str:
        """Hash a file (SHA256)

        Arguments:
            filePath {str} -- File to hash

        Returns:
            str -- Hash value
        """
        sha256 = hashlib.sha256()
    
        with open(filePath, 'rb') as f:
            while True:
                data = f.read(Hasher.BUF_SIZE)
                if not data:
                    break
                sha256.update(data)

        return sha256.hexdigest()
    
    @staticmethod
    def hashList(list: List[Union[str, int, dict, list]]) -> str:
        """Hash a list (SHA256)

        Arguments:
            list {List[Union[str, int, dict, list]]} -- List to hash

        Returns:
            str -- [description]
        """
        sha256 = hashlib.sha256()
        
        for elem in list:
            sha256.update(json.dumps(elem).encode('UTF-16'))
        
        return sha256.hexdigest()