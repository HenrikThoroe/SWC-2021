#pragma once

#include <string>
#include <vector>

#include "pugixml.hpp"

#include "Message.hpp"
#include "Move.hpp"
#include "color.hpp"

namespace App {

    class XMLParser {
        private:
            /// Room id of current game used for sending moves
            char roomId[37];

            /// Current turn on the board
            uint8_t turn = 0;

            uint8_t colorIndex = 0;

            /// Colors that are still in the game
            std::vector<Model::PieceColor> colorsInGame{};
            
        public:
            XMLParser();

            /// No copy constructors allowed
            XMLParser(XMLParser* other) = delete;
            XMLParser(XMLParser& other) = delete;

            /**
             * @brief Split a msg string into separate parsed messages
             * 
             * @param input Input string as received by TCPClient
             * @param result Vector to save parsed messages in
             */
            void splitAndParseMessages(std::string& input, std::vector<Message>& result);

            /**
             * @brief Convert a move into its xml representation to send to server
             * 
             * @param move Move object to convert
             * 
             * @returns Xml representation of move as string
             */
            std::string makeMoveMessage(const Model::Move* move) const;

            /// Get a const pointer to a const vector containing all PieceColors that are still in the game
            const std::vector<Model::PieceColor>* const getColorsInGamePtr() const;

            /**
             * @brief Return the current color, which is eligible to perform the next move.
             * 
             * @returns Current color
             */
            const Model::PieceColor& getCurrentColor() const;
        
        private:
            //? Specific message parsers
            /**
             * @brief Parse a Memento message
             * 
             * @param data Memento xml node
             * @param result Vector to save parsed messages in
             */
            void parseMemento(const pugi::xml_node& data, std::vector<Message>& result);

            /**
             * @brief Parse a Result message
             * 
             * @param data Result xml node
             * @param result Vector to save parsed messages in
             */
            void parseResult(const pugi::xml_node& data, std::vector<Message>& result) const;

            /**
             * @brief Parse a Welcome message
             * 
             * @param data Welcome xml node
             * @param result Vector to save parsed messages in
             */
            void parseWelcome(const pugi::xml_node& data, std::vector<Message>& result) const;

            /**
             * @brief Parse a Joined message
             * 
             * @param node Joined xml node
             * @param result Vector to save parsed messages in
             */
            void parseJoined(const pugi::xml_node& node, std::vector<Message>& result);

            /**
             * @brief Parse an Error message
             * 
             * @param node Error xml node
             * @param result Vector to save parsed messages in
             */
            void parseError(const pugi::xml_node& node, std::vector<Message>& result) const;

            //* Helpers
            /**
             * @brief Translate name of piece to its id
             * 
             * @param pieceName Name of piece
             * 
             * @returns Id of piece
             */
            uint8_t getPieceId(const char* pieceName) const;

            /**
             * @brief Translate id of PieceColor to its name
             * 
             * @param colorId Id of color (enum value)
             * 
             * @returns Name of color
             */
            const char* getColor(const Model::PieceColor& colorId) const;

            /**
             * @brief Calculates the name of the current color.
             * 
             * @returns Name of current color
             */
            const char* getCurrentColorName() const;
    };
    
}
