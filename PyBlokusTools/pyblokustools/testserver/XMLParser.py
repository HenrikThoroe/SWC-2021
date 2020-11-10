from typing import Any, Final, Optional, List
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import Element

from .Message import Message, MementoMsg, ResultMsg, ResultCause, ResultEnd
from .MsgType import MsgType

class XMLParser():
    
    def splitAndParseMessages(self, input: str, result: List[Message]) -> None:
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
            'room'     : self.proxyRoom,
            'prepared' : self.parsePrepared,
            'observed' : self.parseObserved,
            'left'     : self.parseLeft,  
        }
        
        for msg in xmlDoc[0]:
            switch[msg.tag](msg, result)
            
    def proxyRoom(self, data: Element, result: List[Message]) -> None:
        """Proxy to switch different Room Messages

        Arguments:
            data   {Element}       -- Room xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        switch = {
            'memento'        : self.parseMemento,
            'result'         : self.parseResult,
            'error'          : self.parseError,
        }
        roomData = data[0]
        switch.get(data.tag, lambda data, result: None)(roomData, result)
    
    #? Specific message parsers
    def parseMemento(self, data: Element, result: List[Message]) -> None:
        """Parse a Memento message

        Arguments:
            data   {Element}       -- Memento xml node
            result {List[Message]} -- Vector to save parsed messages in
        """
        result.append(
            Message(
                MsgType.GAMESTATE,
                MementoMsg(
                    int(data.get(
                        "turn",
                        default="0"
                        ))
                    )
                )
            )
    
    def parseResult(self, data: Element, result: List[Message]) -> None:
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
        
        score1 = data[0][1]
        score2 = data[0][2]
        
        result.append(
            Message(
                MsgType.RESULT,
                ResultMsg(
                    (int(score1[0][1].text or -1), int(score2[0][1].text or -1)),
                    (
                        ResultEnd(
                        int(
                            score1[0][0].text or 1
                            )
                        ),
                        ResultEnd(
                            int(
                                score2[0][0].text or 1
                                )
                            )
                        ),
                    (getCause(score1.get("cause")), getCause(score2.get("cause"))),
                    )
                )
            )
    
    # for (const pugi::xml_node& msg : xmlDoc.first_child().children()) {
    #     switch (msg.name()[0]) {
    #         // room
    #         case 'r': {
    #             const pugi::xml_node data = msg.child("data");
    #             switch (data.attribute("class").value()[0]) {
    #                 // memento
    #                 case 'm':
    #                     parseMemento(data.first_child(), result);
    #                     break;
                    
    #                 // sc.framework.plugins.protocol.MoveRequest
    #                 case 's':
    #                     result.emplace_back(MsgType::MOVEREQUEST, nullptr);
    #                     break;
                    
    #                 // result
    #                 case 'r':
    #                     parseResult(data, result);
    #                     break;
                    
    #                 // welcomeMessage
    #                 case 'w':
    #                     parseWelcome(data, result);
    #                     break;
                    
    #                 // error
    #                 case 'e':
    #                     parseError(data, result);
    #                     break;
                    
    #                 default:
    #                     throw std::runtime_error("Memento of type '" + std::string(data.name()) + "' could not be parsed");
    #             }
    #             break;
    #         }

    #         // joined
    #         case 'j':
    #             parseJoined(msg, result);
    #             break;
            
    #         // left
    #         case 'l':
    #             result.emplace_back(MsgType::LEFT, nullptr);
    #             break;
            
    #         default:
    #             throw std::runtime_error("Message of type '" + std::string(msg.name()) + "' could not be parsed");
    #             break;
    #     }
    # }
            