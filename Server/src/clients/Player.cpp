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

std::size_t rserver::Player::get_entity_value() const
{
    return this->entity_value;
}

void rserver::Player::set_entity_value(std::size_t const &value)
{
    this->entity_value = value;
}
