#include <optional>

#include "MessageBroker.hpp"

namespace App {
    
    MessageBroker::MessageBroker() {}
    
    MessageBroker::~MessageBroker() {
        tcpClient.disconnect();
    }

    void MessageBroker::connect(const std::string& hostname, const unsigned short& port) {
        std::string address = tcpClient.resolveHostname(hostname);
        tcpClient.connect(address, port);
        sendProtocol();
    }

    std::shared_ptr<MessageQueue> MessageBroker::getMessages() {
        return tcpClient.consumeMessages();
    }

    void MessageBroker::parse(std::string& msg, std::vector<Message>& result) {
        xmlParser.splitAndParseMessages(msg, result);
    }

    void MessageBroker::dispatch(const std::string& msg) { 
        tcpClient.send(msg);
    }

    std::atomic<bool>& MessageBroker::getHasMessagesFlag() {
        return tcpClient.hasMessages;
    }

    const std::vector<Model::PieceColor>* const MessageBroker::getColorsInGamePtr() const {
        return xmlParser.getColorsInGamePtr();
    }

    void MessageBroker::sendProtocol() {
        tcpClient.send("<protocol>");
    }

    void MessageBroker::sendMove(const Model::Move* move) {
        tcpClient.send(xmlParser.makeMoveMessage(move));
    }

    void MessageBroker::sendJoinRequest() {
        tcpClient.send("<join gameType=\"swc_2021_blokus\" />");
    }

    void MessageBroker::sendJoinReservedRequest(const std::string& reservation) {
        tcpClient.send("<joinPrepared reservationCode=\"" + reservation + "\" />");
    }
    
}
