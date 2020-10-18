#include <vector>
#include <stdexcept>
#include <atomic>
#include <vector>
#include <boost/program_options.hpp>

#include "EventLoop.hpp"
#include "debug.hpp"

using namespace boost::program_options;

namespace App {
    // Lifecycle

    EventLoop::EventLoop(int argc, char *argv[]): messageReceivedFlag(messageBroker.getHasMessagesFlag()) {
        // Hostname of gameserver to connect to
        std::string hostname;

        // Listening port of gameserver to connect to
        unsigned short port;

        // Reservation code to redeem with gameserver ("" -> None)
        std::string reservation;

        //? Parse arguments
        options_description optionsDesribtion("C++ client");
        optionsDesribtion.add_options()
            ("host,h", value<std::string>()->default_value("localhost"), "Host")
            ("port,p", value<unsigned short>()->default_value(13050), "Port")
            ("reservation,r", value<std::string>()->default_value(""), "ReservationCode")
        ;

        variables_map varibaleMap;
        store(parse_command_line(argc, argv, optionsDesribtion), varibaleMap);

        hostname    = varibaleMap["host"].as<std::string>();
        port        = varibaleMap["port"].as<unsigned short>();
        reservation = varibaleMap["reservation"].as<std::string>();

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
        std::vector<Message> messages;
        messages.reserve(10);

        while (!gameOver) {
            // Main event loop in here
            if (messageReceivedFlag) {
                //? Messages in queue
                for (std::string& msg : *messageBroker.getMessages()) {
                    messageBroker.parse(msg, messages);

                    for (Message& pMsg : messages) {
                        gameOver = _actOnMessage(pMsg);

                        if (gameOver) {
                            break;
                        }
                    }
                    
                    messages.clear();
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

    inline bool EventLoop::_actOnMessage(const Message& msg) {
        switch (msg.type)
        {
        case MsgType::JOINED:
            /* code */
            break;
        case MsgType::WELCOME:
            /* code */
            break;
        case MsgType::GAMESTATE:
            /* code */
            break;
        case MsgType::MOVEREQUEST:
            /* code */
            break;
        case MsgType::LEFT:
            /* code */
            return true;
            break;
        case MsgType::RESULT:
            /* code */
            return true;
            break;
        case MsgType::EXCEPT:
            /* code */
            return true;
            break;
        case MsgType::PROTOCOLEND:
            /* code */
            return true;
            break;
        case MsgType::UNDEFINED:
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