#include <vector>
#include <stdexcept>

#include "EventLoop.hpp"

namespace App {
    // Lifecycle

    EventLoop::EventLoop() {}
    
    EventLoop::~EventLoop() {}


    // Public interface

    void EventLoop::run(int argc, char *argv[]) {
        // Hostname of gameserver to connect to
        std::string hostname = "localhost";

        // Listening port of gameserver to connect to
        uint8_t port = 13050;

        // Reservation code to redeem with gameserver ("" -> None)
        std::string reservation = "";

        //? Parse arguments
        /* code */

        //? Connect to gameserver
        if (reservation != "") {
            _startReservedConnection(hostname, port, reservation);
        } else {
            _startConnection(hostname, port);
        }

        //? Construct our logic instance
        /* code */

        _loop();
    }


    // Private methods
    
    void EventLoop::_startConnection(const std::string& address, const uint8_t& port) {
        messageBroker.connect(address, port);

        messageBroker.sendJoinRequest();
    }
    
    void EventLoop::_startReservedConnection(const std::string& address, const uint8_t& port, const std::string& reservation) {
        messageBroker.connect(address, port);

        messageBroker.sendJoinReservedRequest(reservation);
    }

    void EventLoop::_loop() {
        bool gameOver = false;

        while (!gameOver) {
            // Main event loop in here
            if (messageBroker.fetchMessages()) {
                //? Messages in queue
                for (const std::string& msg : messageBroker.getMessages()) {
                    gameOver = _actOnMessage(msg);
                    if (gameOver) {
                        break;
                    }
                }

            } else {
                //? Can do background work
                // Shouldnt last to long as we only check for new messages in a new itteration
                _runTask(backgroundQueue.front());
                backgroundQueue.pop();
            }
        }
    }

    bool EventLoop::_actOnMessage(const Communication::Message& msg) {
        switch (msg.type)
        {
        case Communication::MsgType::Joined:
            /* code */
            break;
        case Communication::MsgType::Welcome:
            /* code */
            break;
        case Communication::MsgType::GameState:
            /* code */
            break;
        case Communication::MsgType::MoveRequest:
            /* code */
            break;
        case Communication::MsgType::Left:
            /* code */
            return true;
            break;
        case Communication::MsgType::Result:
            /* code */
            return true;
            break;
        case Communication::MsgType::Error:
            /* code */
            return true;
            break;
        case Communication::MsgType::ProtocolEnd:
            /* code */
            return true;
            break;
        case Communication::MsgType::Undefined:
            throw std::runtime_error("Can not act on Undefined message");
            break;
        default:
            throw std::runtime_error("_actOnMessage switch fell through"); 
        }

        return false;
    }

    void EventLoop::_runTask(const Task& task) const {
        //TODO: implement
    }
}