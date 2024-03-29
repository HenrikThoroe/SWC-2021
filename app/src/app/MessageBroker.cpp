#include <optional>

#include "MessageBroker.hpp"

namespace App {
    
    MessageBroker::MessageBroker() {}
    
    MessageBroker::~MessageBroker() {
        tcpClient.disconnect();
    }

    void MessageBroker::connect(const std::string& hostname, const uint16_t& port) {
        std::string address = tcpClient.resolveHostname(hostname);
        tcpClient.connect(address, port);
        tcpClient.listen();
        sendProtocol();
    }

    std::shared_ptr<MessageQueue> MessageBroker::getMessages() {
        return tcpClient.consumeMessages();
    }

    void MessageBroker::parse(std::string& msg, std::vector<Message>& result) {
        xmlParser.splitAndParseMessages(msg, result);
    }

    void MessageBroker::parseReplay(const std::string& msg, std::vector<Message>& result) {
        xmlParser.splitAndParseReplay(msg, result);
    }

    void MessageBroker::dispatch(const std::string& msg) { 
        tcpClient.send(msg);
    }

    std::atomic<bool>& MessageBroker::getHasMessagesFlag() {
        return tcpClient.hasMessages;
    }

    const TCPClient& MessageBroker::getTCPClient() const {
        return tcpClient;
    }

    const std::vector<Model::PieceColor>* const MessageBroker::getColorsInGamePtr() const {
        return xmlParser.getColorsInGamePtr();
    }

    const std::chrono::high_resolution_clock::time_point* const MessageBroker::getLastMsgReceivedPtr() const {
        return tcpClient.getLastMsgReceivedPtr();
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
