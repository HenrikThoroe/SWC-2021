#include <optional>

#include "MessageBroker.hpp"

namespace App
{
    MessageBroker::MessageBroker() {}
    
    MessageBroker::~MessageBroker() {
        tcpClient.disconnect();
    }

    void MessageBroker::connect(const std::string hostname, const int port) {
        std::string address = tcpClient.resolveHostname(hostname);
        tcpClient.connect(address, port);
        sendProtocol();
    }

    bool MessageBroker::fetchMessages() {
        std::optional<std::shared_ptr<MessageQueue>> messages = tcpClient.consumeMessages()
        if (messages) {
            messageCache = *messages.value();
            return true;
        }

        return false;
    }

    const MessageQueue& MessageBroker::getMessages() const {
        return messageCache;
    }

    void MessageBroker::dispatch(const std::string& msg) { 
        tcpClient.send(msg);
    }

    void MessageBroker::sendProtocol() {
        tcpClient.send("<protocol>");
    }

    void MessageBroker::sendMove(const Model::Move& move) {
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
