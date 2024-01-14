/*
** EPITECH PROJECT, 2023
** clients
** File description:
** PlayersManager
*/

#include <rtype/clients/PlayersManager.hh>
#include <shared_mutex>
#include <vector>

/**
 * @brief Get a player by its port id
 *
 * @param port - asio::port_type - id of player
 * @throws PlayersException - if port_type is not linked to any player
 */
rserver::Player &rserver::PlayersManager::get_by_id(asio::ip::port_type const &port)
{
    for (auto &client : this->players) {
        if (client.get_port() == port)
            return client;
    }
    throw PlayersException();
}

/**
 * @brief Get a player by its entity id
 *
 * @param entity - size_t
 * @throws PlayersException - if entity id is not linked to any player
 */
rserver::Player &rserver::PlayersManager::get_by_entity_id(std::size_t const &entity)
{
    for (auto &client : this->players) {
        if (client.get_entity_value() == entity)
            return client;
    }
    throw PlayersException();
}

rserver::Player &rserver::PlayersManager::get_by_entity_room_id(std::size_t const &entity,
                                                                const std::size_t &room)
{
    for (auto &client : this->players) {
        if (client.get_entity_value() == entity && client.get_room_id() == static_cast<long>(room))
            return client;
    }
    throw PlayersException();
}

/**
 * @brief Add a player to the Manager. Will create a player from the given endpoint
 *
 * @param endpoint - asio::udp::endpoint - to create the player
 * @return Player &
 */
rserver::Player &rserver::PlayersManager::add_player(asio::ip::udp::endpoint &endpoint)
{
    this->players.emplace_back(endpoint);

    return this->players.back();
}

/**
 * @brief Add an already existing player to the Manager
 *
 * @param to_add - Player &
 * @return Player &
 */
rserver::Player &rserver::PlayersManager::add_player(rserver::Player &to_add)
{
    this->players.push_back(to_add);

    return this->players.back();
}

/**
 * @brief Return the number of players in the Manager
 *
 * @return size_t
 */
std::size_t rserver::PlayersManager::length() const
{
    return this->players.size();
}

/**
 * @brief Get all the players in the Manager
 *
 * @return vector<Player>
 */
std::vector<rserver::Player> rserver::PlayersManager::get_all_players() const
{
    return this->players;
}

/**
 * @brief remove a player from the Manager
 * Won't throw error if the player is not in the manager
 *
 * @param player - Player & to delete
 */
void rserver::PlayersManager::remove_player(rserver::Player &player)
{
    for (auto to_erase{this->players.begin()}; to_erase < this->players.end(); to_erase++) {
        if (to_erase->get_port() == player.get_port()) {
            this->players.erase(to_erase);
            break;
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
