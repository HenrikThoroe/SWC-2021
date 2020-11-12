from typing import Union

import socket

class TCPClient():
    """A synchronous TCPClient for communicating with the SWC server

    Arguments:
        hostname {str} -- Hostname of server to connect to
        port     {int} -- Port on which the server listens
    """
    
    MSG_SIGNALS = ("</room>", "</prepared>", "</protocol>")
    
    def __init__(self, hostname: str, port: int) -> None:
        self._buffer = ""
        
        self.connect(hostname, port)
    
    def connect(self, hostname: str, port: int) -> None:
        """Connect to the GameServer

        Arguments:
            hostname {str} -- Hostname of server to connect to
            port     {int} -- Port on which the server listens
        """
        self._socket = socket.create_connection(
            address = (
                socket.gethostbyname(hostname),
                port,
            )
        )
        self._socket.settimeout(2)
        
        self.send('<protocol>')
    
    def disconnect(self) -> None:
        """Disconnect from the SWC server
        """
        self.send('</protocol>')
        self._socket.close()
    
    def send(self, msg: str) -> None:
        """Send a message to the server

        Arguments:
            msg {str} -- Message to send
        """
        self._socket.send(msg.encode("utf-8"))
    
    def receive(self) -> Union[str, bool]:
        """Receive one message

        Returns:
            str -- Message received, or False on timeout
        """
        while True:
            for signal in TCPClient.MSG_SIGNALS: # Multiple xml endings signal a full valid message
                index = self._buffer.find(signal)
                if index != -1:
                    ret          = self._buffer[:index+len(signal)] # Return first message (till end of signal str)
                    self._buffer = self._buffer[index+len(signal):] # Consume message from the buffer
                    
                    return ret
            
            #? Read if no full message was received yet
            try:
                self._buffer += self._socket.recv(4096).decode()
            except socket.timeout:
                return False # We return on timeout to avoid deadlock due to non working clients
