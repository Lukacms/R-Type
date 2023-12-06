/*
** EPITECH PROJECT, 2023
** src
** File description:
** Manager
*/

#include <iostream>
#include <memory>
#include <ostream>
#include <rtype.hh>
#include <rtype/Manager.hh>
#include <rtype/network/Network.hh>

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
        ntw::Communication recv{};
        asio::ip::udp::endpoint remote_endpoint{};

        this->socket.receive_from(asio::buffer(&recv, sizeof(recv)), remote_endpoint);
        this->queue.push_back(remote_endpoint.port(), recv);
        this->handle_command();
    }
}

void rserver::Manager::handle_command()
{
    rserver::Message message{this->queue.pop_front()};

    try {
        Player &player = this->players.get_by_id(message.port);

    } catch (PlayersManager::PlayersExceptions &) {
        this->players.add_player(std::move(message.port));
    }
}
