/*
** EPITECH PROJECT, 2023
** clients
** File description:
** PlayersManager
*/

#include <algorithm>
#include <rtype/clients/PlayersManager.hh>

rserver::Player &rserver::PlayersManager::get_by_id(asio::ip::port_type const &port)
{
    for (auto &client : this->players) {
        if (client.get_port() == port)
            return client;
    }
    throw PlayersExceptions();
}

void rserver::PlayersManager::add_player(asio::ip::port_type port)
{
    this->players.emplace_back(std::move(port));
}

/* exception */
rserver::PlayersManager::PlayersExceptions::PlayersExceptions(std::string p_error)
    : error_msg{std::move(p_error)}
{
}

const char *rserver::PlayersManager::PlayersExceptions::what() const noexcept
{
    return this->error_msg.data();
}
