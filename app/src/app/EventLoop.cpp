#include <vector>
#include <stdexcept>
#include <atomic>

#include "EventLoop.hpp"
#include "debug.hpp"

namespace App {
    // Lifecycle

    EventLoop::EventLoop(int argc, char *argv[]): messageReceivedFlag(messageBroker.getHasMessagesFlag()) {
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
    }
    
    EventLoop::~EventLoop() {}


    // Public interface
    void EventLoop::run() {
        bool gameOver = false;

        while (!gameOver) {
            // Main event loop in here
            if (messageReceivedFlag) {
                //? Messages in queue
                for (const std::string& msg : *messageBroker.getMessages()) {
                    gameOver = _actOnMessage(msg);
                    if (gameOver) {
                        break;
                    }
                }

            } else {
                //? Can do background work
                // Shouldnt last to long as we only check for new messages in a new itteration
                _runTask();
            }
        }
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

    inline bool EventLoop::_actOnMessage(const Communication::Message& msg) {
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

    inline void EventLoop::_runTask() const {
        // (0: done, 1: paused, 2: failed)
        switch (backgroundQueue.front().run(messageReceivedFlag))
        {
        case 0:
            backgroundQueue.pop();
            break;
        case 1:
            Util::debugPrint("Background task has been paused");
            break;
        case 3:
            Util::debugPrint("Background task failed; Exception caught and task discarded");
            break;
        default:
            throw std::runtime_error("Got unexpected backgroundTask return code.");
            break;
        }
    }
}