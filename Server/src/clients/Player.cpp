/* ** EPITECH PROJECT, 2023
** clients
** File description:
** Player
*/

#include <algorithm>
#include <rtype.hh>
#include <rtype/clients/Player.hh>

/* constructor / destructor */
rserver::Player::Player(asio::ip::udp::endpoint p_endpoint) : endpoint{std::move(p_endpoint)}
{
    DEBUG(("%s%s%d%s", INFOS.data(), NEW_CLIENT.data(), this->endpoint.port(), ENDL));
}

rserver::Player::~Player() = default;

/* {
    DEBUG(("%s%d%s", DEL_CLIENT.data(), this->endpoint.port(), ENDL));
} */

rserver::Player::Player(rserver::Player &&to_move)
    : endpoint{std::move(to_move.endpoint)}, entity_value{std::move(to_move.entity_value)}
{
}

rserver::Player::Player(const rserver::Player &to_copy)
    : endpoint{to_copy.endpoint}, entity_value{to_copy.entity_value}, status{to_copy.status},
      level{to_copy.level}, room_id{to_copy.room_id}
{
}

rserver::Player &rserver::Player::operator=(Player &&to_move)
{
    this->endpoint = std::move(to_move.endpoint);
    this->entity_value = std::move(to_move.entity_value);

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

const std::size_t &rserver::Player::get_entity_value() const
{
    return this->entity_value;
}

const rserver::PlayerStatus &rserver::Player::get_status() const
{
    return this->status;
}

void rserver::Player::set_status(const PlayerStatus &new_status)
{
    this->status = new_status;
}

void rserver::Player::set_entity_value(std::size_t const &value)
{
    this->entity_value = value;
}

void rserver::Player::lock()
{
    this->mutex.lock();
}

void rserver::Player::unlock()
{
    this->mutex.unlock();
}

void rserver::Player::level_up()
{
    if (this->level < 3)
        this->level += 1;
}

std::size_t rserver::Player::get_level() const
{
    return this->level;
}

const long &rserver::Player::get_room_id() const
{
    return this->room_id;
}

void rserver::Player::set_room_id(const long &new_id)
{
    this->room_id = new_id;
}
