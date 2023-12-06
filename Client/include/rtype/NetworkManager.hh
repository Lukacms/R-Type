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
            ~NetworkManager() = default;
            NetworkManager(NetworkManager const &other) = delete;
            NetworkManager(NetworkManager &&other) noexcept;
            NetworkManager &operator=(NetworkManager const &other) = delete;
            NetworkManager &operator=(NetworkManager &&other) noexcept;
            void run();

        private:
            asio::io_context io_context;
            asio::ip::udp::resolver resolver;
            asio::ip::udp::endpoint receiver_endpoint;
            asio::ip::udp::socket socket;
    };
} // namespace rclient
