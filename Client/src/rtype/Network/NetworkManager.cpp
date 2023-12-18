/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** networkManager.cpp
*/

#include <iostream>
#include <rtype/Network/NetworkManager.hh>

using asio::ip::udp;

rclient::NetworkManager::NetworkManager(const std::string &host, const std::string &port)
    : m_resolver(m_io_context),
      m_receiver_endpoint(*m_resolver.resolve(asio::ip::udp::v4(), host, port).begin()),
      m_socket(m_io_context, asio::ip::udp::v4())
{
}

void rclient::NetworkManager::fetch_messages()
{
    while (m_socket.available() > 0) {
        std::array<char, MAX_SIZE> received{};
        asio::ip::udp::endpoint sender_endpoint;
        m_socket.receive_from(asio::buffer(received), sender_endpoint);
        m_queue.emplace_back(received);
    }
}

void rclient::NetworkManager::send_message()
{
}

std::deque<std::array<char, rclient::MAX_SIZE>> &rclient::NetworkManager::get_message_queue()
{
    return m_queue;
}
