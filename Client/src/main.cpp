/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <asio.hpp>
#include <iostream>
#include <iterator>
#include <rtype.hh>
#include <rtype/network/Network.hh>
#include <unistd.h>

using asio::ip::udp;

int main(int argc, char *argv[])
{
    ntw::Communication communication{};

    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        asio::io_context io_context;
        udp::resolver resolver(io_context);
        udp::endpoint receiver_endpoint =
            *resolver.resolve(udp::v4(), "127.0.0.1", argv[1]).begin();
        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 1> send_buf = {'k'};
        socket.send_to(asio::buffer(send_buf, 1), receiver_endpoint);
        // std::array<char, sizeof(communication)> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(asio::buffer(&communication, sizeof(communication)),
                                         receiver_endpoint);

        if (len != sizeof(communication)) {
            std::cerr << "Received unexpected data size." << std::endl;
            return 1;
        }

        std::cout << (communication.type == ntw::Start ? "oui\n" : "non\n");
        std::cout << "String address: " << &communication.args << std::endl;
        std::cout << "String length: " << communication.args.size() << std::endl;
        std::cout << "String content: " << communication.args << std::endl;
        // std::cout.write(recv_buf.data(), len);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "ouin ?" << ENDL;

    return 0;
}
