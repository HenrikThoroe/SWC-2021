#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <queue>

#include "TCPClient.hpp"
#include "XMLParser.hpp"
#include "Move.hpp"
#include "Task.hpp"
#include "Message.hpp"
#include "MsgType.hpp"

namespace App {   
    
    /// Interface for everything communication related (TCP, XML)
    class MessageBroker {
        private:
            ///TCPClient for communication with server
            TCPClient   tcpClient = TCPClient();

            ///XMLParser to parse and serialize xml messages from to to the server
            XMLParser    xmlParser = XMLParser();
            
        public:
            MessageBroker(/* args */);
            ~MessageBroker();

            /**
             * @brief Connect to the server and send <protocol>
             * 
             * @param hostname Server address
             * @param port Port to connect to
             */
            void connect(const std::string hostname, const int port);

            /**
             * @brief Consume all recieved Messages
             * 
             * @returns Shared Pointer to MessageQueue
             */
            std::shared_ptr<MessageQueue> getMessages();

            /**
             * @brief Parse a msg string to a Message struct
             * 
             * @param msg MultiMsg string to parse
             * @param result Vector to store parsed messages in
             * 
             * @returns Void -> Stores parsed messages in 'result' param
             */
            void parse(std::string& msg, std::vector<Message>& result);

            /**
             * @brief Dispatch a Message to the gameserver
             * 
             * @param msg Message to send
             */
            void dispatch(const std::string& msg);

            ///Create and dispatch a <protocol> message
            void sendProtocol();

            ///Create and dispatch a joinRequest
            void sendJoinRequest();

            /**
             * @brief Create and dispatch a joinRequest with a reservation
             * 
             * @param reservation Code to use
             */
            void sendJoinReservedRequest(const std::string& reservation);

            /**
             * @brief Send a move to the gameserver
             * 
             * @param move MoveObject to serialize and send
             */
            void sendMove(const Model::Move* move);
            
            /**
             * @brief Get the TCPClient´s hasMessages
             * 
             * @returns Atomic bool
             */
            std::atomic<bool>& getHasMessagesFlag();
    };
    
} // namespace App
