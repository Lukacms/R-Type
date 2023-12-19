/*
** EPITECH PROJECT, 2023
** clients
** File description:
** PlayersManager
*/

#include <algorithm>
#include <asio/registered_buffer.hpp>
#include <rtype/clients/PlayersManager.hh>
#include <vector>

rserver::Player &rserver::PlayersManager::get_by_id(asio::ip::port_type const &port)
{
    for (auto &client : this->players) {
        if (client.get_port() == port)
            return client;
    }
    throw PlayersException();
}

rserver::Player &rserver::PlayersManager::get_by_entity_id(std::size_t &entity)
{
    for (auto &client : this->players) {
        if (client.get_entity_value() == entity)
            return client;
    }
    throw PlayersException();
}

rserver::Player &rserver::PlayersManager::add_player(asio::ip::udp::endpoint &endpoint,
                                                     asio::ip::udp::socket & /* socket */)
{
    this->players.emplace_back(endpoint);

    return this->players.back();
}

std::size_t rserver::PlayersManager::length() const
{
    return this->players.size();
}

const std::vector<rserver::Player> &rserver::PlayersManager::get_all_players() const
{
    return this->players;
}

/* exception */
rserver::PlayersManager::PlayersException::PlayersException(std::string p_error)
    : error_msg{std::move(p_error)}
{
}

const char *rserver::PlayersManager::PlayersException::what() const noexcept
{
    return this->error_msg.data();
}
