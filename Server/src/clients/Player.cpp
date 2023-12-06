/*
** EPITECH PROJECT, 2023
** clients
** File description:
** Player
*/

#include <iostream>
#include <rtype.hh>
#include <rtype/clients/Player.hh>

/* constructor / destructor */
rserver::Player::Player(asio::ip::port_type p_port) : port{std::move(p_port)}
{
    std::cout << INFOS << NEW_CLIENT << this->port << ENDL;
}

rserver::Player::Player(rserver::Player &&to_move) : port{std::move(to_move.port)}
{
    std::cout << INFOS << MOVE_CLIENT << this->port << ENDL;
}

rserver::Player::~Player()
{
    std::cout << INFOS << DEL_CLIENT << this->port << ENDL;
}

/* operator overload */
rserver::Player &rserver::Player::operator=(Player &&to_move)
{
    this->port = std::move(to_move.port);

    std::cout << INFOS << MOVE_CLIENT << this->port << ENDL;
    return *this;
}

bool rserver::Player::operator==(asio::ip::port_type &p_port) const
{
    return p_port == this->port;
}

/* getters / setters */
asio::ip::port_type rserver::Player::get_port() const
{
    return this->port;
}
