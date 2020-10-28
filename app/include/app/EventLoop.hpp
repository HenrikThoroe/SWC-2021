#pragma once

#include <atomic>
#include <string>
#include <inttypes.h>

#include "MessageBroker.hpp"
#include "GameManager.hpp"
#include "Message.hpp"
#include "MsgType.hpp"

namespace App {

    /// The main EventLoop of the Blokus AI, managing the connection to the server, parsing and best move calculation
    class EventLoop {
        private:
            /// Middleware between EventLoop and tcpClient
            App::MessageBroker messageBroker = MessageBroker();

            /// Flag for signaling message received
            std::atomic<bool>& messageReceivedFlag;

            /// Queue for scheduled background tasks
            mutable std::queue<Task> backgroundQueue{};

            /// Middleware between EventLoop and GameState
            Logic::GameManager gameManager;

        public:
            /**
             * @brief Construct a new EventLoop
             * 
             * @param argc Number of console arguments
             * @param argv Array of pointers to console argument strings (first argument is own filename)
             */
            EventLoop(int argc, char* argv[]);

            /// No copy constructors allowed
            EventLoop(EventLoop* other) = delete;
            EventLoop(EventLoop& other) = delete;

            /// Destructor
            ~EventLoop();

            /// Start execution of the main EventLoop -> Yield control to the EL
            void run();
            
        private:
            /**
             * @brief Starts a connection with the gameserver
             * 
             * @param address Address of the gameserver
             * @param port Port of the gameserver
             */
            void startConnection(const std::string& address, const unsigned short& port);

            /**
             * @brief Starts a reserved connection with the gameserver
             * 
             * @param address Address of the gameserver
             * @param port Port of the gameserver
             * @param reservation Reservation code to join specific match
             */
            void startReservedConnection(const std::string& address, const uint8_t& port, const std::string& reservation);

            /// Run actual eventLoop
            void loop();

            /**
             * @brief Acts on the message recieved and respond accordingly
             * 
             * @param msg Message to act on
             * 
             * @returns Is game over
             */
            bool actOnMessage(const Message& msg);

            /// Run a background task
            void runTask() const;
    };
    
}
