#include "MessageBroker.hpp"

namespace App
{
    MessageBroker::MessageBroker() {}
    
    MessageBroker::~MessageBroker() {
        tcpClient.disconnect();
    }

    void MessageBroker::connect(std::string hostname, int port) {
        std::string address = tcpClient.resolveHostname(hostname);
        tcpClient.connect(address, port);
        sendProtocol();
    }

    void MessageBroker::dispatch(std::string& msg) {
        tcpClient.send(msg);
    }

    void MessageBroker::sendProtocol() {
        tcpClient.send("<protocol>");
    }

    void MessageBroker::sendMove(Model::Move& move) {
        std::string msg = xmlParser.parse(move);
        tcpClient.send(msg);
    }

    void MessageBroker::sendJoinRequest() {
        //! Change to current gameType
        tcpClient.send('<join gameType="swc_2021_blokus" />');
    }

    void MessageBroker::sendJoinReservedRequest(const std::string& reservation) {
        tcpClient.send('<joinPrepared reservationCode="' + reservation + '" />');
    }


    
}
