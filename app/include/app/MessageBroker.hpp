#pragma once

#include <string>

#include "TCPClient.hpp"
#include "Move.hpp"
#include "Message.hpp"
#include "MsgType.hpp"

namespace App
{
    class MessageBroker
    {
    private:
        App::TCPClient tcpClient = TCPClient();
        App:XMLParser  xmlParser = XMLParser();
        /* data */
    public:
        MessageBroker(/* args */);
        ~MessageBroker();

        /**
         * @brief Connect to the server and send <protocol>
         * 
         * @param hostname Server address
         * @param port Port to connect to
         */
        void connect(std::string hostname, int port);

        /**
         * @brief Dispatch a Message to the gameserver
         * 
         * @param msg Message to send
         */
        void dispatch(std::string& msg);

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
        void sendMove(Model::Move& move);

    };

} // namespace App
