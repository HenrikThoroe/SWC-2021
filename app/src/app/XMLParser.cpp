#include <array>
#include <stdexcept>
#include <cstring>
#include <sstream>

#include "XMLParser.hpp"
#include "XMLStringWriter.hpp"
#include "PieceCollection.hpp"
#include "color.hpp"
#include "Rotation.hpp"
#include "Vector2D.hpp"
#include "Position.hpp"

namespace App {

    XMLParser::XMLParser() {}

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
        input.insert(0, "<A>");
        input.append("</A>");

        pugi::xml_document xmlDoc;
        xmlDoc.load_string(input.data());
        
        for (const pugi::xml_node& msg : xmlDoc.first_child().children()) {
            switch (msg.name()[0]) {
                // room
                case 'r': {
                    const pugi::xml_node data = msg.child("data");
                    switch (data.attribute("class").value()[0]) {
                        // memento
                        case 'm':
                            parseMemento(data.first_child(), result);
                            break;
                        
                        // sc.framework.plugins.protocol.MoveRequest
                        case 's':
                            result.emplace_back(MsgType::MOVEREQUEST, nullptr);
                            break;
                        
                        // result
                        case 'r':
                            parseResult(data, result);
                            break;
                        
                        // welcomeMessage
                        case 'w':
                            parseWelcome(data, result);
                            break;
                        
                        // error
                        case 'e':
                            parseError(data, result);
                            break;
                        
                        default:
                            throw std::runtime_error("Memento of type '" + std::string(data.name()) + "' could not be parsed");
                    }
                    break;
                }

                // joined
                case 'j':
                    parseJoined(msg, result);
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


        // ? Append protocolMsg to back
        if (protocolEnd) {
            result.emplace_back(MsgType::PROTOCOLEND, nullptr);
        }
    }

    void XMLParser::splitAndParseReplay(const std::string& input, std::vector<Message>& result) {
        //? Split replay string by newline
        std::stringstream ss{input};

        uint8_t turn = 0;

        // Turn -> Color
        auto denormalizeColor = [](uint8_t color) -> uint8_t {
            switch (color) {                
                // Blue
                case 0:
                    return 2;
                
                // Yellow
                case 1:
                    return 4;

                // Red
                case 2:
                    return 1;

                // Green
                case 3:
                    return 3;
                
                default:
                    throw std::runtime_error("Could not denormalize color '" + std::to_string(color) + "'");
            }
        };

        // Get next turns color
        auto getNextTurnColor = [&turn, &denormalizeColor]() -> Model::PieceColor {
            return static_cast<Model::PieceColor>(denormalizeColor(turn % 4));
        };

        for (std::string line; std::getline(ss, line, '\n');) {
            if (line.rfind("startPiece:", 0) == 0) {
                //? Start piece
                result.emplace_back(
                    MsgType::GAMESTATE,
                    MementoMsg(
                        getPieceId(line.substr(11, std::string::npos).c_str()),
                        std::nullopt,
                        turn,
                        getNextTurnColor()
                    )
                );
            } else {
                //? Normal move

                pugi::xml_document xmlDoc;
                xmlDoc.load_string(line.data());

                pugi::xml_node move = xmlDoc.first_child();
                pugi::xml_node piece = move.first_child();
                if (move.attribute("class").value()[15] == 'k') {
                    //* Skip move
                    result.emplace_back(MsgType::GAMESTATE, MementoMsg(0, std::nullopt, turn, getNextTurnColor()));
                } else {
                    //* Set move
                    result.emplace_back(MsgType::GAMESTATE, MementoMsg(0, computeMoveIndex(piece), turn, getNextTurnColor()));
                }
            }

            turn += 1;
        }

        // Remove last msg as the server will send it when we join
        result.pop_back();
    }

    std::string XMLParser::makeMoveMessage(const Model::Move* move) const {
        pugi::xml_document xmlDoc;

        pugi::xml_node roomNode = xmlDoc.append_child("room");
        roomNode.append_attribute("roomId").set_value(roomId);
        if (move != nullptr) {
            pugi::xml_node dataNode = roomNode.append_child("data");
            dataNode.append_attribute("class").set_value("sc.plugin2021.SetMove");

            pugi::xml_node pieceNode = dataNode.append_child("piece");

            //? Color
            pieceNode.append_attribute("color").set_value(getColor(move->color));

            //? Kind
            pieceNode.append_attribute("kind").set_value(Model::PieceCollection::getPiece(move->pieceId).name);

            //? Rotation
            switch (move->rotation) {
                case Model::Rotation::ZERO:
                    pieceNode.append_attribute("rotation").set_value("NONE");
                    pieceNode.append_attribute("isFlipped").set_value("false");
                    break;
                
                case Model::Rotation::ONEHALFPI:
                    pieceNode.append_attribute("rotation").set_value("RIGHT");
                    pieceNode.append_attribute("isFlipped").set_value("false");
                    break;

                case Model::Rotation::PI:
                    pieceNode.append_attribute("rotation").set_value("MIRROR");
                    pieceNode.append_attribute("isFlipped").set_value("false");
                    break;
                
                case Model::Rotation::THREEHALFPI:
                    pieceNode.append_attribute("rotation").set_value("LEFT");
                    pieceNode.append_attribute("isFlipped").set_value("false");
                    break;
                
                case Model::Rotation::ZERO_FLIPPED:
                    pieceNode.append_attribute("rotation").set_value("NONE");
                    pieceNode.append_attribute("isFlipped").set_value("true");
                    break;
                
                case Model::Rotation::ONEHALFPI_FLIPPED:
                    pieceNode.append_attribute("rotation").set_value("RIGHT");
                    pieceNode.append_attribute("isFlipped").set_value("true");
                    break;
                
                case Model::Rotation::PI_FLIPPED:
                    pieceNode.append_attribute("rotation").set_value("MIRROR");
                    pieceNode.append_attribute("isFlipped").set_value("true");
                    break;
                
                case Model::Rotation::THREEHALFPI_FLIPPED:
                    pieceNode.append_attribute("rotation").set_value("LEFT");
                    pieceNode.append_attribute("isFlipped").set_value("true");
                    break;
                
                default:
                    throw std::runtime_error("Rotation with value '" + std::to_string(static_cast<uint8_t>(move->rotation)) + "' not found");
            }

            //? Coordinates
            int8_t minX = 127;
            int8_t minY = 127;
            for (const Util::Position& piece : move->getOccupiedPositions()) {
                if (piece.x < minX) minX = piece.x;
                if (piece.y < minY) minY = piece.y;
            }

            pugi::xml_node positionNode = pieceNode.append_child("position");
            positionNode.append_attribute("x").set_value(minX);
            positionNode.append_attribute("y").set_value(minY);

        } else {
            pugi::xml_node data = roomNode.append_child("data");
            data.append_attribute("class").set_value("sc.plugin2021.SkipMove");

            data.append_child("color").append_child(pugi::node_pcdata).set_value(getCurrentColorName());
        }

        Util::XMLStringWriter xmlStringWriter;
        xmlDoc.print(xmlStringWriter, " ", pugi::format_default);

        return xmlStringWriter.result;
    }

    const std::vector<Model::PieceColor>* const XMLParser::getColorsInGamePtr() const {
        return &colorsInGame;
    }

    //? Specific message parsers

    void XMLParser::parseMemento(const pugi::xml_node& data, std::vector<Message>& result) {
        turn = data.attribute("turn").as_int();

        switch (turn % 4) {
            case 0:
                turnColor  = Model::PieceColor::BLUE;
                break;
            case 1:
                turnColor  = Model::PieceColor::YELLOW;
                break;
            case 2:
                turnColor  = Model::PieceColor::RED;
                break;
            case 3:
                turnColor  = Model::PieceColor::GREEN;
                break;
            
            default:
                throw std::runtime_error("Could not determine turnColor for turn '" + std::to_string(turn) + "'");
        }

        colorsInGame.clear();
        for (const pugi::xml_node& color : data.child("validColors").children()) {
            switch (color.child_value()[0]) {
                // Blue
                case 'B':
                    colorsInGame.push_back(Model::PieceColor::BLUE);
                    break;

                // Yellow
                case 'Y':
                    colorsInGame.push_back(Model::PieceColor::YELLOW);
                    break;

                // Red
                case 'R':
                    colorsInGame.push_back(Model::PieceColor::RED);
                    break;

                // Green
                case 'G':
                    colorsInGame.push_back(Model::PieceColor::GREEN);
                    break;

                default:
                    break;
            }
        }

        pugi::xml_node piece = data.child("lastMove").first_child();
        if (piece) {
            //* Not first move -> LastMove
            if (piece.name()[0] == 'p') {
                // SetMove
                result.emplace_back(MsgType::GAMESTATE, MementoMsg(0, computeMoveIndex(piece), turn, turnColor));
            } else {
                // SkipMove
                result.emplace_back(MsgType::GAMESTATE, MementoMsg(0, std::nullopt, turn, turnColor));
            }
        } else {
            result.emplace_back(MsgType::GAMESTATE, MementoMsg(getPieceId(data.attribute("startPiece").value()), std::nullopt, turn, turnColor));
        }
    }

    void XMLParser::parseResult(const pugi::xml_node& data, std::vector<Message>& result) const {
        pugi::xml_node score1 = data.first_child().next_sibling();
        pugi::xml_node score2 = score1.next_sibling();

        // Lambda that determines the game ending cause
        auto getCause = [](const char* txt) -> ResultMsg::ResultCause {
            if (!strcmp(txt, "REGULAR")) {
                return ResultMsg::ResultCause::REGULAR;
            } else if (!strcmp(txt, "LEFT")) {
                return ResultMsg::ResultCause::LEFT;
            } else if (!strcmp(txt, "RULE_VIOLATION")) {
                return ResultMsg::ResultCause::RULE_VIOLATION;
            } else if (!strcmp(txt, "SOFT_TIMEOUT")) {
                return ResultMsg::ResultCause::SOFT_TIMEOUT;
            } else if (!strcmp(txt, "HARD_TIMEOUT")) {
                return ResultMsg::ResultCause::HARD_TIMEOUT;
            }

            throw std::runtime_error("Non valid gameEnding cause encountered: '" + std::string(txt) + "'");
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

    void XMLParser::parseWelcome(const pugi::xml_node& data, std::vector<Message>& result) const {
        // Checks the first character of the color attribute on the data node in the welcome message to determine own PlayerColor
        result.emplace_back(MsgType::WELCOME, data.attribute("color").value()[0] == 'O' ? Model::PlayerColor::BLUE : Model::PlayerColor::RED);
    }
    
    void XMLParser::parseJoined(const pugi::xml_node& node, std::vector<Message>& result) {
        strcpy(roomId, node.attribute("roomId").value());
        result.emplace_back(MsgType::JOINED, std::string(roomId));
    }

    void XMLParser::parseError(const pugi::xml_node& data, std::vector<Message>& result) const {
        Util::XMLStringWriter xmlStringWriter;
        data.print(xmlStringWriter, " ", pugi::format_default);

        result.emplace_back(MsgType::EXCEPT, xmlStringWriter.result);
    }

    int XMLParser::computeMoveIndex(const pugi::xml_node piece) const {
        //? Rotation
        const char* pieceRotation = piece.attribute("rotation").value();
        uint8_t rotation;
        if (!strcmp(pieceRotation, "NONE")) {
            rotation = 0;
        } else if (!strcmp(pieceRotation, "RIGHT")) {
            rotation = 1;
        } else if (!strcmp(pieceRotation, "MIRROR")) {
            rotation = 2;
        } else if (!strcmp(pieceRotation, "LEFT")) {
            rotation = 3;
        }

        if (piece.attribute("isFlipped").as_bool()) {
            rotation += 4;
        }

        //? PieceID
        uint8_t pieceId = getPieceId(piece.attribute("kind").value());

        //? Color
        uint8_t color;
        switch (piece.attribute("color").value()[0]) {
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
                throw std::runtime_error("Color '" + std::string(piece.attribute("color").value()) + "' not found");
        }

        //? X, Y
        pugi::xml_node position = piece.child("position");

        uint8_t x = position.attribute("x").as_int();
        uint8_t y = position.attribute("y").as_int();

        //? Origin
        int8_t minX = 127;
        int8_t minY = 127;
        for (const Util::Vector2D& piece : std::get<0>(Model::PieceCollection::getPiece(pieceId).getRotation(rotation))) {
            if (piece.x < minX) minX = piece.x;
            if (piece.y < minY) minY = piece.y;
        }

        //? Calculate index
        // x + y * maxX + rotation * maxX * maxY + id * maxRotations * maxX * maxY + color * maxId * maxRotations * maxX * maxY
        return (x - minX + (y - minY) * 20) + (rotation * 400 + pieceId * 3200) + (color * 20 * 20 * 8 * 21);
    }

    uint8_t XMLParser::getPieceId(const char* pieceName) const {
        if (!strcmp(pieceName, "MONO")) {
            return 0;
        } else if (!strcmp(pieceName, "DOMINO")) {
            return 1;
        } else if (!strcmp(pieceName, "TRIO_L")) {
            return 2;
        } else if (!strcmp(pieceName, "TRIO_I")) {
            return 3;
        } else if (!strcmp(pieceName, "TETRO_I")) {
            return 4;
        } else if (!strcmp(pieceName, "TETRO_L")) {
            return 5;
        } else if (!strcmp(pieceName, "TETRO_O")) {
            return 6;
        } else if (!strcmp(pieceName, "TETRO_T")) {
            return 7;
        } else if (!strcmp(pieceName, "TETRO_Z")) {
            return 8;
        } else if (!strcmp(pieceName, "PENTO_I")) {
            return 9;
        } else if (!strcmp(pieceName, "PENTO_U")) {
            return 10;
        } else if (!strcmp(pieceName, "PENTO_L")) {
            return 11;
        } else if (!strcmp(pieceName, "PENTO_V")) {
            return 12;
        } else if (!strcmp(pieceName, "PENTO_P")) {
            return 13;
        } else if (!strcmp(pieceName, "PENTO_W")) {
            return 14;
        } else if (!strcmp(pieceName, "PENTO_R")) {
            return 15;
        } else if (!strcmp(pieceName, "PENTO_X")) {
            return 16;
        } else if (!strcmp(pieceName, "PENTO_Z")) {
            return 17;
        } else if (!strcmp(pieceName, "PENTO_Y")) {
            return 18;
        } else if (!strcmp(pieceName, "PENTO_T")) {
            return 19;
        } else if (!strcmp(pieceName, "PENTO_S")) {
            return 20;
        }

        throw std::runtime_error("Piece of type '" + std::string(pieceName) + "' not found");
    }

    const char* XMLParser::getColor(const Model::PieceColor& colorId) const {
        switch (colorId) {
            case Model::PieceColor::RED:
                return "RED";

            case Model::PieceColor::BLUE:
                return "BLUE";

            case Model::PieceColor::GREEN:
                return "GREEN";

            case Model::PieceColor::YELLOW:
                return "YELLOW";

            default:
                throw std::runtime_error("Color with value '" + std::to_string(static_cast<uint8_t>(colorId)) + "' not found");
        }
    }

    const Model::PieceColor& XMLParser::getCurrentColor() const {
        return turnColor;
    }

    const char* XMLParser::getCurrentColorName() const {
        return getColor(turnColor);
    }

}
