#pragma once

#include <string>
#include <vector>

#include "pugixml.hpp"

#include "Message.hpp"

namespace App
{
    class XMLParser {
        private:
            // Room id of current game used for sending moves
            std::string roomId;
        public:
            XMLParser();

            // No copy constructors allowed
            XMLParser(XMLParser* other) = delete;
            XMLParser(XMLParser& other) = delete;
            ~XMLParser();

            /**
             * @brief Split a msg string into separate parsed messages
             * 
             * @param input Input string as received by TCPClient
             * @param result Vector to save parsed messages in
             */
            void splitAndParseMessages(std::string& input, std::vector<Message>& result);
        
        private:
            //? Specific message parsers
            /**
             * @brief Parse a Memento message
             * 
             * @param data Memento xml node
             * @param result Vector to save parsed messages in
             */
            void _parseMemento(const pugi::xml_node& data, std::vector<Message>& result) const;

            /**
             * @brief Parse a Result message
             * 
             * @param data Result xml node
             * @param result Vector to save parsed messages in
             */
            void _parseResult(const pugi::xml_node& data, std::vector<Message>& result) const;

            /**
             * @brief Parse a Welcome message
             * 
             * @param data Welcome xml node
             * @param result Vector to save parsed messages in
             */
            void _parseWelcome(const pugi::xml_node& data, std::vector<Message>& result) const;

            /**
             * @brief Parse a Joined message
             * 
             * @param node Joined xml node
             * @param result Vector to save parsed messages in
             */
            void _parseJoined(const pugi::xml_node& node);

            /**
             * @brief Parse an Error message
             * 
             * @param node Error xml node
             * @param result Vector to save parsed messages in
             */
            void _parseError(const pugi::xml_node& node, std::vector<Message>& result) const;

            //* Helpers
            /**
             * @brief Translate name of piece to its id
             * 
             * @param pieceName Name of piece
             * 
             * @returns Id of piece
             */
            uint8_t _getPieceId(const std::string& pieceName) const;


    };
} // namespace App
