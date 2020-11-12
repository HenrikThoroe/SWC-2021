from typing import Any, Final, Optional, List
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import Element

from .Message import Message, MementoMsg, ResultMsg, PreparedMsg, ResultCause, ResultEnd
from .MsgType import MsgType

class XMLParser():
    """Namespace for everything relating to XML
    """
    def __new__(cls, *args, **kwargs):
        """Prevent the XMLParser class from being instantiated

        Raises:
            TypeError: Instantiation exception
        """
        raise TypeError("XMLParser class may not be instantiated")
    
    #? Public interface
    @staticmethod
    def xmlToString(xml: Element) -> str:
        """Convert an xml Element to an xml string

        Arguments:
            xml {Element} -- Element to convert

        Returns:
            str -- XML string
        """
        return ET.tostring(xml, encoding="unicode", method='xml')[:-1]
    
    @staticmethod  
    def splitAndParseMessages(input: str, result: List[Message]) -> None:
        """Split a msg string into separate parsed messages

        Arguments:
            input {str}            -- Input string as received by TCPClient
            result {List[Message]} -- List to save parsed messages in
        """
        
        #? Filter out non xml compliant messages
        input = input.replace("<protocol>", "")
        
        protocolEnd = False
        if input.find("</protocol>") != -1:
            input = input.replace("</protocol>", "")
            protocolEnd = True
        
        #? Parse compliant messages
        # Wrap xml compliant messages for easier parsing
        input = f"<A>{input}</A>"
        
        xmlDoc = ET.fromstring(input)
        
        switch = {
            'room'     : XMLParser._proxyRoom,
            'left'     : XMLParser._parseLeft,
            'prepared' : XMLParser._parsePrepared,
            'observed' : XMLParser._parseObserved,  
        }
        for msg in xmlDoc:
            switch.get(msg.tag, XMLParser._parseError)(msg, result)
        
        if protocolEnd:
            result.append(
                Message(
                    MsgType.PROTOCOLEND,
                    None
                )
            )

    #? Proxies
    @staticmethod
    def _proxyRoom(data: Element, result: List[Message]) -> None:
        """Proxy to switch different Room Messages

        Arguments:
            data   {Element}       -- Room xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        switch = {
            'memento'        : XMLParser._parseMemento,
            'result'         : XMLParser._parseResult,
            'error'          : XMLParser._parseError,
        }
        roomData = data[0]
        switch.get(roomData.get("class", "error"), lambda data, result: None)(roomData, result)
    
    #? Specific message parsers
    @staticmethod
    def _parseMemento(data: Element, result: List[Message]) -> None:
        """Parse a Memento message

        Arguments:
            data   {Element}       -- Memento xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        data = data[0] # Get first child
        result.append(
            Message(
                MsgType.GAMESTATE,
                MementoMsg(
                    int(data.get(
                        "turn",
                        default="0"
                        )
                    )
                )
            )
        )
    
    @staticmethod
    def _parseResult(data: Element, result: List[Message]) -> None:
        """Parse a Result message

        Arguments:
            data   {Element}       -- Result xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        def getCause(cause: Optional[str]) -> ResultCause:
            """Converts a game ending cause string to a ResultCause enum value

            Arguments:
                cause {Optional[str]} -- Game ending cause

            Returns:
                ResultCause -- Corresponding enum value
            """
            if cause == "REGULAR":
                return ResultCause.REGULAR
            elif cause == "LEFT":
                return ResultCause.LEFT
            elif cause == "RULE_VIOLATION":
                return ResultCause.RULE_VIOLATION
            elif cause == "SOFT_TIMEOUT":
                return ResultCause.SOFT_TIMEOUT
            elif cause == "HARD_TIMEOUT":
                return ResultCause.HARD_TIMEOUT
            
            raise RuntimeError(f"Tried to convert invalid game ending cause '{cause}' to enum value")
        
        score1 = data[1]
        score2 = data[2]
        
        result.append(
            Message(
                MsgType.RESULT,
                ResultMsg(
                    (int(score1[1].text or -1), int(score2[1].text or -1)),
                    (
                        ResultEnd(
                            int(
                                score1[0].text or 1
                            )
                        ),
                        ResultEnd(
                            int(
                                score2[0].text or 1
                            )
                        ),
                    ),
                    (getCause(score1.get("cause")), getCause(score2.get("cause"))),
                )
            )
        )
    
    @staticmethod
    def _parseError(data: Element, result: List[Message]) -> None:
        """Parse an Error message

        Arguments:
            data   {Element}       -- Error xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        result.append(
            Message(
                MsgType.EXCEPT,
                XMLParser.xmlToString(data),
            )
        )
    
    @staticmethod
    def _parseLeft(data: Element, result: List[Message]) -> None:
        """Parse a Left message

        Arguments:
            data   {Element}       -- Left xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        result.append(
            Message(
                MsgType.LEFT,
                data.get("roomId", ""),
            )
        )
    
    @staticmethod
    def _parsePrepared(data: Element, result: List[Message]) -> None:
        """Parse a Prepared message

        Arguments:
            data   {Element}       -- Prepared xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        result.append(
            Message(
                MsgType.PREPARED,
                PreparedMsg(
                    data.get("roomId", ""),
                    (
                       data[0].text or "",
                       data[1].text or "",
                    )
                )
            )
        )
    
    @staticmethod
    def _parseObserved(data: Element, result: List[Message]) -> None:
        """Parse an Observed message

        Arguments:
            data   {Element}       -- Observed xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        result.append(
            Message(
                MsgType.OBSERVED,
                data.get("roomId", ""),
            )
        )
