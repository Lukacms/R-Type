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
rserver::Player::Player(asio::ip::udp::endpoint p_endpoint) : endpoint{std::move(p_endpoint)}
{
    std::cout << INFOS << NEW_CLIENT << this->endpoint << ENDL;
}

rserver::Player::Player(rserver::Player &&to_move) : endpoint{std::move(to_move.endpoint)}
{
    std::cout << INFOS << MOVE_CLIENT << this->endpoint << ENDL;
}

rserver::Player::~Player()
{
    std::cout << INFOS << DEL_CLIENT << this->endpoint << ENDL;
}

/* operator overload */
rserver::Player &rserver::Player::operator=(Player &&to_move)
{
    this->endpoint = std::move(to_move.endpoint);

    std::cout << INFOS << MOVE_CLIENT << this->endpoint << ENDL;
    return *this;
}

bool rserver::Player::operator==(asio::ip::port_type &port) const
{
    return port == this->endpoint.port();
}

/* getters / setters */
asio::ip::port_type rserver::Player::get_port() const
{
    return this->endpoint.port();
}

asio::ip::udp::endpoint rserver::Player::get_endpoint() const
{
    return this->endpoint;
}
