#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <string>
#include <optional>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

typedef std::queue<std::string> MessageQueue;

namespace App
{
    class TCPClient
    {
    private:
        // Mutex to lock multithreaded access
        std::mutex mutex;
        
        // Queue that holds all received messages in order
        std::shared_ptr<MessageQueue> messages = std::make_shared<MessageQueue>();

        // Bool that indicates messages state
        bool hasMessages = false;

        // Flag if there is a thread currently listenting
        bool listening = false;

        // Flag to indicate if client is connected to server
        bool connected = false;

        // Buffer that holds received data
        boost::asio::streambuf receiveBuffer;

        // The IoService Object used by boost asio
        boost::asio::io_service ioService;

        // The socket used by boost asio
        boost::asio::ip::tcp::socket socket{ioService};
    public:
        TCPClient(/* args */);
        ~TCPClient();
        
        /**
         * @brief Connect to the server
         * 
         * @param address Resolved server addres (IP)
         * @param port Port to connect to
         */
        void connect(std::string address, int port);

        // Resolve a hostname to an address (IP)
        std::string resolveHostname(std::string hostname);

        // Disconnect from server (gracefully)
        void disconnect();

        /**
         * @brief Get all received messages and empty the MessageQueue (only if not empty)
         * 
         * @returns Optional SharedPointer to the consumed MessageQueue
         */
        std::optional<std::shared_ptr<MessageQueue>> consumeMessages();

        // Listen for incoming messages (Async)
        void listen();

        /**
         * @brief Send messages to server (Sync)
         * 
         * @param message Message to send to server
         */
        void send(std::string& message);
    private:
        /**
         * @brief Handler called when a Message is read
         * 
         * @param ec Refference to an errorCode that accured during read
         * @param bytes_transferred Number of bytes transferred
         */
        void on_read(const boost::system::error_code& ec, std::size_t& bytes_transferred);

    }; 
    
} // namespace App
