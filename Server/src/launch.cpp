/*
** EPITECH PROJECT, 2023
** src
** File description:
** launch
*/

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <array>
#include <asio.hpp>
#include <iostream>
#include <string>

int launch()
{
    try {
        asio::io_context io_context;
        asio::ip::udp::socket socket{io_context,
                                     asio::ip::udp::endpoint{asio::ip::udp::v4(), 8081}};

        while (true) {
            std::array<char, 1> recv_buf{};
            asio::ip::udp::endpoint remote_endpoint{};

            socket.receive_from(asio::buffer(recv_buf), remote_endpoint);
            std::string message{"oui\r\n"};
            asio::error_code ignored{};
            socket.send_to(asio::buffer(message), remote_endpoint, 0, ignored);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
