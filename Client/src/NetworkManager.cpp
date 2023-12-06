/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** networkManager.cpp
*/

#include <iostream>
#include <rtype/NetworkManager.hh>

using asio::ip::udp;

rclient::NetworkManager::NetworkManager(const std::string &host, const std::string &port)
    : resolver(io_context),
      receiver_endpoint(*resolver.resolve(asio::ip::udp::v4(), host, port).begin()),
      socket(io_context, asio::ip::udp::v4())
{
}

void rclient::NetworkManager::run()
{
    while (true) {
        try {
            std::array<char, 1> send_buf = {{0}};
            socket.send_to(asio::buffer(send_buf), receiver_endpoint);

            std::array<char, 128> recv_buf;
            asio::ip::udp::endpoint sender_endpoint;
            const size_t len = socket.receive_from(asio::buffer(recv_buf), sender_endpoint);

            std::cout.write(recv_buf.data(), len);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
