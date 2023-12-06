/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#pragma once

#include <asio.hpp>

using asio::ip::udp;

namespace rclient
{
    class NetworkManager
    {
        public:
            NetworkManager(const std::string &host, const std::string &port);
            void run();

        private:
            asio::io_context io_context;
            asio::ip::udp::resolver resolver;
            asio::ip::udp::endpoint receiver_endpoint;
            asio::ip::udp::socket socket;
    };
} // namespace rclient
