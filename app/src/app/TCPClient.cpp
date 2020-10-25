#include <stdexcept>
#include <thread>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>

#include "TCPClient.hpp"

namespace App {

    TCPClient::TCPClient() {
        messages->reserve(5);
    }

    void TCPClient::connect(const std::string& address, const int port) {
        // Lock the mutex to avoid date races
        std::lock_guard g{mutex};

        socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port));

        connected = true;
    }

    std::string TCPClient::resolveHostname(const std::string& hostname) {
        boost::asio::ip::tcp::resolver resolver(ioService);
        boost::asio::ip::tcp::resolver::query query(hostname, "");
        boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
        boost::asio::ip::tcp::endpoint endpoint = *i;
        return endpoint.address().to_string();
    }

    void TCPClient::disconnect() {
        // Lock the mutex to avoid date races
        std::lock_guard g{mutex};
        
        connected = false;

        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket.close();
    }

    std::shared_ptr<MessageQueue> TCPClient::consumeMessages() {
        // Lock the mutex to avoid date races
        std::lock_guard g{mutex};

        std::shared_ptr<MessageQueue> newRet = std::make_shared<MessageQueue>();
        newRet->reserve(5);

        std::swap(newRet, messages);

        hasMessages = false;

        return newRet;
    }

    void TCPClient::listen() {
        // Lock the mutex to avoid date races
        std::lock_guard g{mutex};

        if (listening) return;
        listening = true;
        ioService.reset();

        boost::asio::async_read_until(socket, receiveBuffer, "</room>", [this](const boost::system::error_code& ec, const std::size_t bytes_transferred){
            this->on_read(ec, bytes_transferred);
        });

        std::thread listener([&] {
            ioService.run();
            std::lock_guard tg{mutex};
            listening = false;
            });
        listener.detach();
    }

    void TCPClient::send(const std::string& message) {
        boost::system::error_code errorCode;
        boost::asio::write(socket, boost::asio::buffer(message), errorCode);
        if (errorCode) {
            throw std::runtime_error("Sending failed: " + errorCode.message());
        }
    }

    void TCPClient::on_read(const boost::system::error_code& ec, const std::size_t& bytes_transferred) {
        // Lock the mutex to avoid date races
        std::lock_guard g{mutex};

        if ((boost::asio::error::eof == ec) ||
        (boost::asio::error::connection_reset == ec)) {
            if (connected) throw std::runtime_error("Connection to server lost");

            return;
        }

        messages->emplace_back(
            boost::asio::buffers_begin(receiveBuffer.data()),
            boost::asio::buffers_begin(receiveBuffer.data()) + bytes_transferred //- 7 //!
        );

        receiveBuffer.consume(bytes_transferred);

        hasMessages = true;

        //! This model always listens in the background, remove this call and call .listen manually in the event loop
        //! if you want to manually reschedule listening for messages. This is more async but may bump performance a little
        //TODO: Test performance implications
        boost::asio::async_read_until(socket, receiveBuffer, "</room>", [this](const boost::system::error_code& ec, const std::size_t bytes_transferred){
            this->on_read(ec, bytes_transferred);
        });
    }
    
} // namespace App
