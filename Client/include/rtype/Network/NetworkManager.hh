/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the client core
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <deque>

using asio::ip::udp;

namespace rclient
{
    constexpr int MAX_SIZE{128};

    class NetworkManager
    {
        public:
            NetworkManager(const std::string &host, const std::string &port);
            ~NetworkManager() = default;
            NetworkManager(NetworkManager const &other) = delete;
            NetworkManager(NetworkManager &&other) = delete;
            NetworkManager &operator=(NetworkManager const &other) = delete;
            NetworkManager &operator=(NetworkManager &&other) = delete;

            void fetch_messages();
            void send_message();

            [[nodiscard]] std::deque<std::array<char, MAX_SIZE>> &get_message_queue();

        private:
            asio::io_context m_io_context;
            asio::ip::udp::resolver m_resolver;
            asio::ip::udp::endpoint m_receiver_endpoint;
            asio::ip::udp::socket m_socket;
            std::deque<std::array<char, MAX_SIZE>> m_queue{};
    };
} // namespace rclient
