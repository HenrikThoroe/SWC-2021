#include <array>
#include <stdexcept>

#include "XMLParser.hpp"
#include "PieceCollection.hpp"
#include "color.hpp"
#include "Vector2D.hpp"

namespace App
{
    XMLParser::XMLParser() {}
    XMLParser::~XMLParser() {}

    void XMLParser::splitAndParseMessages(std::string& input, std::vector<Message>& result) {
        //? Filter out non xml compliant messages
        std::size_t protocolPos = input.find("<protocol>");
        if (protocolPos != std::string::npos) {
            input.erase(protocolPos, 10);
        }

        bool protocolEnd = false;
        std::size_t protocolEndPos = input.find("</protocol>");
        if (protocolEndPos != std::string::npos) {
            input.erase(protocolEndPos, 11);
            protocolEnd = true;
        }

        //? Parse compliant messages
        // Wrap xml compliant messages for easier parsing
        input.insert(0, "<>");
        input.append("</>");

        pugi::xml_document xmlDoc;
        xmlDoc.load_string(input.data());

        //TODO: Check if this is only the outer <>...</> node
        for (pugi::xml_node _ : xmlDoc.children()) {
            for (pugi::xml_node msg : _.children()) {

                switch (msg.name()[0])
                {
                // room
                case 'r':
                    pugi::xml_node data = msg.child("data");
                    switch (data.attribute("class").value()[0])
                    {
                    // memento
                    case 'm':
                        _parseMemento(data.first_child(), result);
                        break;
                    
                    // sc.framework.plugins.protocol.MoveRequest
                    case 's':
                        result.emplace_back(MsgType::MOVEREQUEST, nullptr);
                        break;
                    
                    // result
                    case 'r':
                        _parseResult(data, result);
                        break;
                    
                    // welcomeMessage
                    case 'w':
                        _parseWelcome(data, result);
                        break;
                    
                    // error
                    case 'e':
                        _parseError(data, result);
                        break;
                    
                    default:
                        throw std::runtime_error("Memento of type '" + std::string(data.name()) + "' could not be parsed");
                        break;
                    }
                    break;
                
                // joined
                case 'j':
                    _parseJoined(msg);
                    break;
                
                // left
                case 'l':
                    result.emplace_back(MsgType::LEFT, nullptr);
                    break;
                
                default:
                    throw std::runtime_error("Message of type '" + std::string(msg.name()) + "' could not be parsed");
                    break;
                }
            }
        }


        // ? Append protocolMsg to back
        if (protocolEnd) {
            result.emplace_back(MsgType::PROTOCOLEND, nullptr);
        }
    }

    inline void XMLParser::_parseMemento(const pugi::xml_node& data, std::vector<Message>& result) const {
        pugi::xml_node piece = data.child("lastMove").first_child();
        
        if (piece) {
            //* Not first move -> LastMove
            //? Rotation
            //! Is RIGHT -> ONEHALFPI? Or is it THREEHALFPI?!
            std::string pieceRotation = piece.attribute("rotation").value();
            uint8_t rotation;
            if (pieceRotation == "NONE") {
                rotation = 0;
            } else if (pieceRotation == "RIGHT") {
                rotation = 1;
            } else if (pieceRotation == "MIRROR") {
                rotation = 2;
            } else if (pieceRotation == "LEFT") {
                rotation = 3;
            }

            if (piece.attribute("rotation").as_bool()) {
                rotation += 4;
            }

            //? PieceID
            uint8_t pieceId = _getPieceId(piece.attribute("kind").value());

            //? Color
            uint8_t color;
            switch (piece.attribute("color").value()[0])
            {
            // Red
            case 'R':
                color = 0;
                break;
            
            // Blue
            case 'B':
                color = 1;
                break;

            // Green
            case 'G':
                color = 2;
                break;

            // Yellow
            case 'Y':
                color = 3;
                break;
            
            default:

                throw std::runtime_error("Color '" + piece.attribute("color").value() + "' not found");
                break;
            }

            //? X, Y
            pugi::xml_node position = piece.first_child();
            uint8_t x = position.attribute("x").as_int();
            uint8_t y = position.attribute("y").as_int();

            //? Origin
            int8_t minX = 127;
            int8_t minY = 127;
            for (const Util::Vector2D piece: std::get<0>(Model::PieceCollection::getPiece(pieceId).getRotation(rotation))) {
                if (piece.x < minX) minX = piece.x;
                if (piece.y < minY) minX = piece.x;
            }

            //? Calculate index
            // x + y * maxX + rotation * maxX * maxY + id * maxRotations * maxX * maxY + color * maxId * maxRotations * maxX * maxY
            const int index = ((x-minX + y-minY) * 20) + (rotation * 400 + pieceId * 3200) + (color * 20 * 20 * 8 * 21);

            result.emplace_back(MsgType::GAMESTATE, MementoMsg(0, index));
        } else {
            result.emplace_back(MsgType::GAMESTATE, MementoMsg(_getPieceId(data.attribute("startPiece").value()), 0));
        }
    }

    inline void XMLParser::_parseResult(const pugi::xml_node& data, std::vector<Message>& result) const {
        pugi::xml_node score1 = data.first_child().next_sibling();
        pugi::xml_node score2 = score1.next_sibling();

        // Lambda that determines the game ending cause
        auto getCause = [](std::string txt) -> ResultMsg::ResultCause {
            if (txt == "REGULAR") {
                return ResultMsg::ResultCause::REGULAR;
            } else if (txt == "LEFT") {
                return ResultMsg::ResultCause::LEFT;
            } else if (txt == "RULE_VIOLATION") {
                return ResultMsg::ResultCause::RULE_VIOLATION;
            } else if (txt == "SOFT_TIMEOUT") {
                return ResultMsg::ResultCause::SOFT_TIMEOUT;
            } else if (txt == "HARD_TIMEOUT") {
                return ResultMsg::ResultCause::HARD_TIMEOUT;
            }

            throw std::runtime_error("Non valid gameEnding cause encountered: '" + txt + "'");
        };
        
        //! Maybe use std::unique_pointer to avoid copy?
        result.emplace_back(
            MsgType::RESULT,
            ResultMsg(
                //? Score (Game points)
                {
                    static_cast<uint8_t>(score1.first_child().next_sibling().text().as_int()),
                    static_cast<uint8_t>(score2.first_child().next_sibling().text().as_int()),
                },
                //? End (Win points)
                {
                    static_cast<ResultMsg::ResultEnd>(score1.first_child().text().as_int()),
                    static_cast<ResultMsg::ResultEnd>(score2.first_child().text().as_int()),
                },
                //? Cause
                {
                    getCause(score1.attribute("cause").value()),
                    getCause(score2.attribute("cause").value()),
                }
            )
        );
    }

    inline void XMLParser::_parseWelcome(const pugi::xml_node& data, std::vector<Message>& result) const {
        result.emplace_back(MsgType::WELCOME, data.attribute("color").value() == "one" ? Model::PlayerColor::BLUE : Model::PlayerColor::RED);
    }
    
    inline void XMLParser::_parseJoined(const pugi::xml_node& node) {
        roomId = node.attribute("roomId").value();
    }

    inline uint8_t _getPieceId(const std::string& pieceName) const {
        if (pieceName == "MONO") {
            return 0;
        } else if (pieceName == "DOMINO") {
            return 1;
        } else if (pieceName == "TRIO-L") {
            return 2;
        } else if (pieceName == "TRIO-I") {
            return 3;
        } else if (pieceName == "TETRO-I") {
            return 4;
        } else if (pieceName == "TETRO-L") {
            return 5;
        } else if (pieceName == "TETRO-O") {
            return 6;
        } else if (pieceName == "TETRO-T") {
            return 7;
        } else if (pieceName == "TETRO-Z") {
            return 8;
        } else if (pieceName == "PENTO-I") {
            return 9;
        } else if (pieceName == "PENTO-U") {
            return 10;
        } else if (pieceName == "PENTO-L") {
            return 11;
        } else if (pieceName == "PENTO-V") {
            return 12;
        } else if (pieceName == "PENTO-P") {
            return 13;
        } else if (pieceName == "PENTO-W") {
            return 14;
        } else if (pieceName == "PENTO-R") {
            return 15;
        } else if (pieceName == "PENTO-X") {
            return 16;
        } else if (pieceName == "PENTO-Z") {
            return 17;
        } else if (pieceName == "PENTO-Y") {
            return 18;
        } else if (pieceName == "PENTO-T") {
            return 19;
        } else if (pieceName == "PENTO-S") {
            return 20;
        }

        throw std::runtime_error("Piece of type '" + pieceName + "' not found");
    }
} // namespace App
