/*
** EPITECH PROJECT, 2023
** clients
** File description:
** PlayersManager
*/

#include <algorithm>
#include <asio/registered_buffer.hpp>
#include <rtype/clients/PlayersManager.hh>
#include <shared_mutex>
#include <vector>

rserver::Player &rserver::PlayersManager::get_by_id(asio::ip::port_type const &port)
{
    for (auto &client : this->players) {
        if (client.get_port() == port)
            return client;
    }
    throw PlayersException();
}

rserver::Player &rserver::PlayersManager::get_by_entity_id(std::size_t const &entity)
{
    for (auto &client : this->players) {
        if (client.get_entity_value() == entity)
            return client;
    }
    throw PlayersException();
}

rserver::Player &rserver::PlayersManager::add_player(asio::ip::udp::endpoint &endpoint)
{
    this->players.emplace_back(endpoint);

    return this->players.back();
}

rserver::Player &rserver::PlayersManager::add_player(rserver::Player &to_add)
{
    this->players.push_back(to_add);

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

void rserver::PlayersManager::remove_player(rserver::Player &player)
{
    for (auto to_erase{this->players.begin()}; to_erase < this->players.end(); to_erase++) {
        {
            std::shared_lock<std::shared_mutex> lock{to_erase->mutex};

            if (to_erase->get_port() == player.get_port()) {
                this->players.erase(to_erase);
                break;
            }
        }
    }
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
