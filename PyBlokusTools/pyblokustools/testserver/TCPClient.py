import socket

class TCPClient():
    """A synchronous TCPClient for communicating with the SWC server

    Arguments:
        hostname {str} -- Hostname of server to connect to
        port     {int} -- Port on which the server listens
    """
    def __init__(self, hostname: str, port: int) -> None:
        self.buffer = ""
        
        self.connect(hostname, port)
    
    def connect(self, hostname: str, port: int) -> None:
        """Connect to the GameServer

        Arguments:
            hostname {str} -- Hostname of server to connect to
            port     {int} -- Port on which the server listens
        """
        self.socket = socket.create_connection(
            address = (
                socket.gethostbyname(hostname),
                port,
            )
        )
    
    def send(self, msg: str) -> None:
        """Send a message to the server

        Arguments:
            msg {str} -- Message to send
        """
        self.socket.send(msg.encode("utf-8"))
    
    def receive(self) -> str:
        """Recieve one message

        Returns:
            str -- Message recieved
        """
        while True:
            index = self.buffer.find("</room>")
            if index != -1:
                ret         = self.buffer[:index+7] # Return first message (till </room>)
                self.buffer = self.buffer[index+7:] # Consume message from the buffer
                
                return ret
            
            #? Read if no full message was received yet
            self.buffer += self.socket.recv(4096).decode("utf-8")
