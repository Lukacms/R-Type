/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <asio.hpp>
#include <iostream>
#include <rtype/NetworkManager.hh>
#include <rtype/network/Network.hh>

using asio::ip::udp;

int main(int argc, char *argv[])
{
    const ntw::Communication communication{};
    const std::string host = argv[1];
    const std::string port = "8080";

    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        rclient::NetworkManager network_manager(host, port);
        network_manager.run();
        std::cout << (communication.type == ntw::Start ? "oui\n" : "non\n");
        std::cout << "String address: " << &communication.args << std::endl;
        std::cout << "String length: " << communication.args.size() << std::endl;
        std::cout << "String content: " << communication.args.data() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
