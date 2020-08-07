import hashlib

class Hasher():
    BUF_SIZE = 65536
    
    @staticmethod
    def hash(filePath: str) -> str:
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