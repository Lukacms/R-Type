/* ** EPITECH PROJECT, 2023
** clients
** File description:
** Player
*/

#include <algorithm>
#include <rtype.hh>
#include <rtype/clients/Player.hh>

/* constructor / destructor */
/**
 * @brief Constructor for Player class, need to be given an endpoint
 *
 * @param p_endpoint - asio::udp::endpoint
 */
rserver::Player::Player(asio::ip::udp::endpoint p_endpoint) : endpoint{std::move(p_endpoint)}
{
    DEBUG(("%s%s%d%s", INFOS.data(), NEW_CLIENT.data(), this->endpoint.port(), ENDL));
}

rserver::Player::~Player() = default;

/* {
    DEBUG(("%s%d%s", DEL_CLIENT.data(), this->endpoint.port(), ENDL));
} */

/**
 * @brief Move constructor for Player class
 *
 * @param to_move - Player &&
 */
rserver::Player::Player(rserver::Player &&to_move)
    : endpoint{std::move(to_move.endpoint)}, entity_value{std::move(to_move.entity_value)}
{
}

/**
 * @brief Copy constructor for Player class
 *
 * @param to_copy - const Player &
 */
rserver::Player::Player(const rserver::Player &to_copy)
    : endpoint{to_copy.endpoint}, entity_value{to_copy.entity_value}, status{to_copy.status},
      level{to_copy.level}, room_id{to_copy.room_id}
{
}

/**
 * @brief Move operator for client class
 *
 * @param to_move - Player &&
 * @return - reference to Player
 */
rserver::Player &rserver::Player::operator=(Player &&to_move)
{
    this->endpoint = std::move(to_move.endpoint);
    this->entity_value = std::move(to_move.entity_value);

    return *this;
}

/**
 * @brief Equality operator for players
 *
 * @param port - asio::port_type
 * @return bool
 */
bool rserver::Player::operator==(asio::ip::port_type &port) const
{
    return port == this->endpoint.port();
}

/* getters / setters */
/**
 * @brief Get the port of the player's endpoint
 *
 * @return asio::port_type
 */
asio::ip::port_type rserver::Player::get_port() const
{
    return this->endpoint.port();
}

/**
 * @brief Get the player's endpoint
 *
 * @return asio::udp::endpoint
 */
asio::ip::udp::endpoint rserver::Player::get_endpoint() const
{
    return this->endpoint;
}

/**
 * @brief Get the player's entity value
 *
 * @return size_t
 */
const std::size_t &rserver::Player::get_entity_value() const
{
    return this->entity_value;
}

/**
 * @brief Get the player's status
 *
 * @return PlayerStatus { Lobby, Room, Game }
 */
const rserver::PlayerStatus &rserver::Player::get_status() const
{
    return this->status;
}

/**
 * @brief Set the player status to desired value
 *
 * @param new_status - PlayerStatus
 */
void rserver::Player::set_status(const PlayerStatus &new_status)
{
    this->status = new_status;
}

/**
 * @brief Set the entity value to desired value
 *
 * @param value - size_t
 */
void rserver::Player::set_entity_value(std::size_t const &value)
{
    this->entity_value = value;
}

/**
 * @brief Lock the Player's mutex
 */
void rserver::Player::lock()
{
    this->mutex.lock();
}

/**
 * @brief Unlock the player's mutex
 */
void rserver::Player::unlock()
{
    this->mutex.unlock();
}

/**
 * @brief Increase the player's level by one, if it's under 3
 * Will allow the player to have better weapons
 */
void rserver::Player::level_up()
{
    if (this->level < 3)
        this->level += 1;
}

/**
 * @brief Get the player's level
 *
 * @return size_t
 */
std::size_t rserver::Player::get_level() const
{
    return this->level;
}

/**
 * @brief Get the player's room id
 * To see which room it's in
 *
 * @return long (can be -1 if player is not in room)
 */
const long &rserver::Player::get_room_id() const
{
    return this->room_id;
}

/**
 * @brief Set room id for player, when they join one
 *
 * @param new_id long
 */
void rserver::Player::set_room_id(const long &new_id)
{
    this->room_id = new_id;
}
