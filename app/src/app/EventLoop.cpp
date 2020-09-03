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
        App::TCPClient* tcpClient = messageBroker.getTCPClient();
        tcpClient->connectWithIP(tcpClient->resolveToIP(address), port);

        messageBroker.dispatch("<protocol>");
        messageBroker.dispatch(messageBroker.createJoinRequestMessage());
    }
    
    void EventLoop::_startReservedConnection(const std::string& address, const uint8_t& port, const std::string& reservation) {
        App::TCPClient* tcpClient = messageBroker.getTCPClient();
        tcpClient->connectWithIP(tcpClient->resolveToIP(address), port);

        messageBroker.dispatch("<protocol>");
        messageBroker.dispatch(messageBroker.createJoinReservedRequestMessage(reservation));
    }

    void EventLoop::_loop() {
        bool gameOver = false;

        while (!gameOver) {
            // Main event loop in here
            for (const Communication::Message& msg : messageBroker.getMessages()) {
                gameOver = _actOnMessage(msg);
                if (gameOver) {
                    messageBroker.clearCache();
                    break;
                }
            }
            messageBroker.clearCache();
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

}