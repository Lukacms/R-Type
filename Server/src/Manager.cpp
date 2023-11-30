/*
** EPITECH PROJECT, 2023
** src
** File description:
** Manager
*/

#include <iostream>
#include <rtype.hh>
#include <rtype/Manager.hh>

/* constructors and destructors */

/**
 * @brief Default constructor
 *
 * @param port port_type, default to 8080
 */
rserver::Manager::Manager(asio::ip::port_type port)
    : socket{this->context, asio::ip::udp::endpoint{asio::ip::udp::v4(), port}}
{
}

rserver::Manager::Manager(rserver::Manager &&to_move) : socket{std::move(to_move.socket)}
{
}

rserver::Manager::~Manager()
{
    std::cout << "bye" << ENDL;
}

/* operator overload */

rserver::Manager &rserver::Manager::operator=(Manager &&to_move)
{
    this->socket = std::move(to_move.socket);

    return *this;
}

/* methods */
void rserver::Manager::launch(asio::ip::port_type port)
{
    try {
        Manager manager{port};

        manager.do_loop();
    } catch (std::exception &e) {
        std::cout << e.what() << ENDL;
    }
}

void rserver::Manager::do_loop()
{
    while (true) {
        std::array<char, 1> recv_buf{};
        asio::ip::udp::endpoint remote_endpoint{};

        this->socket.receive_from(asio::buffer(recv_buf), remote_endpoint);
        std::string message{"oui\r\n"};
        asio::error_code ignored{};
        this->socket.send_to(asio::buffer(message), remote_endpoint, 0, ignored);
    }
}
