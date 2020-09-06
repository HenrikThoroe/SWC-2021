#pragma once

#include "TCPClient.hpp"

namespace App
{
    class MessageBroker
    {
    private:
        App::TCPClient tcpClient;
        /* data */
    public:
        MessageBroker(/* args */);
        ~MessageBroker();
    };

} // namespace App
