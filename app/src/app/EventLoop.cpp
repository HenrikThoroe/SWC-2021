#include <vector>
#include <stdexcept>
#include <atomic>
#include <vector>
#include <any>
#include <boost/program_options.hpp>

#include "EventLoop.hpp"
#include "debug.hpp"

using namespace boost::program_options;

namespace App {

    EventLoop::EventLoop(int argc, char* argv[]): messageReceivedFlag(messageBroker.getHasMessagesFlag()), gameManager(messageBroker.getColorsInGamePtr()) {
        // Hostname of gameserver to connect to
        std::string hostname;

        // Listening port of gameserver to connect to
        uint16_t port;

        // Reservation code to redeem with gameserver ("" -> None)
        std::string reservation;

        //? Parse arguments
        options_description optionsDesribtion("C++ client");
        optionsDesribtion.add_options()
            ("host,h", value<std::string>()->default_value("localhost"), "Host")
            ("port,p", value<uint16_t>()->default_value(13050), "Port")
            ("reservation,r", value<std::string>()->default_value(""), "ReservationCode")
        ;

        variables_map varibaleMap;
        store(parse_command_line(argc, argv, optionsDesribtion), varibaleMap);

        hostname    = varibaleMap["host"].as<std::string>();
        port        = varibaleMap["port"].as<uint16_t>();
        reservation = varibaleMap["reservation"].as<std::string>();

        //? Connect to gameserver
        if (reservation != "") {
            startReservedConnection(hostname, port, reservation);
        } else {
            startConnection(hostname, port);
        }
    }
    
    EventLoop::~EventLoop() {}

    //* Public interface

    void EventLoop::run() {
        bool gameOver = false;
        std::vector<Message> messages;
        messages.reserve(10);

        while (!gameOver) {
            // Main event loop in here
            if (messageReceivedFlag) {
                //? Messages in queue
                std::shared_ptr<MessageQueue> msgQueue = messageBroker.getMessages();
                for (std::string& msg : *msgQueue) {
                    messageBroker.parse(msg, messages);

                    for (Message& pMsg : messages) {
                        gameOver = actOnMessage(pMsg);

                        if (gameOver) {
                            break;
                        }
                    }
                    
                    messages.clear();
                }
            } else {
                //? Can do background work
                // Shouldnt last to long as we only check for new messages in a new itteration
                runTask();
            }
        }
    }

    //? Private methods

    void EventLoop::startConnection(const std::string& address, const uint16_t& port) {
        messageBroker.connect(address, port);

        messageBroker.sendJoinRequest();
    }
    
    void EventLoop::startReservedConnection(const std::string& address, const uint8_t& port, const std::string& reservation) {
        messageBroker.connect(address, port);

        messageBroker.sendJoinReservedRequest(reservation);
    }

    inline bool EventLoop::actOnMessage(const Message& msg) {
        switch (msg.type) {
            case MsgType::JOINED:
                std::cout << "\033[1;37mJoined room '\033[1;36m" + std::any_cast<std::string>(msg.payload) + "\033[1;37m'\033[0m" << std::endl;
                break;
            
            case MsgType::WELCOME:
                std::cout << "\033[1;37mGot assigned colors ";

                if (std::any_cast<Model::PlayerColor>(msg.payload) == Model::PlayerColor::BLUE) {
                    std::cout << "\033[1;34mBLUE \033[1;37m& \033[1;31mRED\033[0m";
                    gameManager.setColor(Model::PlayerColor::BLUE);
                } else {
                    std::cout << "\033[1;33mYELLOW \033[1;37m& \033[1;32mGREEN\033[0m";
                    gameManager.setColor(Model::PlayerColor::RED);
                }

                std::cout << std::endl;
                break;
            
            case MsgType::GAMESTATE:
                gameManager.updateWithMemento(std::any_cast<MementoMsg>(msg.payload));
                break;
            
            case MsgType::MOVEREQUEST:
                Util::debugPrint("\033[1;37mReceived MoveRequest\033[0m");
                messageBroker.sendMove(gameManager.moveRequest());
                break;
            
            case MsgType::LEFT:
                std::cout << "\033[1;37mOpponent left the game\033[0m" << std::endl;
                return true;
            
            case MsgType::RESULT:
                std::cout << "\033[1;37mThe results are in\033[0m" << std::endl;
                return true;
            
            case MsgType::EXCEPT:
                std::cout << "\033[1;31mAn error occurred\033[0m" << std::endl;
                return true;
            
            case MsgType::PROTOCOLEND:
                Util::debugPrint("\033[1;37mReceived ProtocolEnd\033[0m");
                return true;
            
            case MsgType::UNDEFINED:
                throw std::runtime_error("Can not act on Undefined message");

            default:
                throw std::runtime_error("_actOnMessage switch fell through"); 
        }

        return false;
    }

    inline void EventLoop::runTask() const {
        switch (backgroundQueue.front().run(messageReceivedFlag)) {
            case TaskStatus::DONE:
                backgroundQueue.pop();
                break;
            
            case TaskStatus::PAUSED:
                Util::debugPrint("Background task has been paused");
                break;
            
            case TaskStatus::FAILED:
                Util::debugPrint("Background task failed; Exception caught and task discarded");
                break;
            
            default:
                throw std::runtime_error("Got unexpected backgroundTask return code.");
        }
    }

}
