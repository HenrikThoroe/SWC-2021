#pragma once

#include <string>
#include <queue>

#include "TCPClient.hpp"
#include "Move.hpp"
#include "Task.hpp"
#include "Message.hpp"
#include "MsgType.hpp"

namespace App
{   
    /**
     * @brief Interface for everything communication related (TCP, XML)
     * 
     */
    class MessageBroker
    {
    private:
        // TCPClient for communication with server
        App::TCPClient   tcpClient = TCPClient();

        // XMLParser to parse and serialize xml messages from to to the server
        App:XMLParser    xmlParser = XMLParser();

        //! Switch to pointer?
        // Cache for messages recieved from server
        App:MessageQueue messageCache;
        
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
         * @brief Fetch messages from TCPLayer
         * 
         * @returns Messages in queue
         */
        bool fetchMessages();

        // Get all messages recieved since the last call
        const MessageQueue& getMessages() const;

        /**
         * @brief Dispatch a Message to the gameserver
         * 
         * @param msg Message to send
         */
        void dispatch(const std::string& msg);

        // Create and dispatch a <protocol> message
        void sendProtocol();

        // Create and dispatch a joinRequest
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
        void sendMove(const Model::Move& move);

    };

} // namespace App
