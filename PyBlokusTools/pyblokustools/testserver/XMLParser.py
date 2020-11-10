from typing import Any, Final, List
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import Element

from .Message import Message, MementoMsg, ResultMsg
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
            'room'   : self.proxyRoom,
            'joined' : self.parseJoined,
            'left'   : self.parseLeft,  
        }
        
        for msg in xmlDoc[0]:
            msg: Element
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
            'welcomeMessage' : self.parseLeft,
            'error'          : self.parseError,
        }
        roomData = data[0]
        switch.get(data, lambda data, result: None)(roomData, result)
    
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
                data.get("turn")
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
            