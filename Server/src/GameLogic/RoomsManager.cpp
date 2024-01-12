/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** RoomsManager
*/

#include <iostream>
#include <rtype/GameLogic/RoomsManager.hh>

/* methods */
/**
 * @brief Allow player to join a random room that is available. If not, throw exception
 *
 * @param player - Player &
 */
void rserver::game::RoomsManager::join_random_room(rserver::Player &player)
{
    for (auto &room : this->rooms) {
        if (room.get_status() == RoomStatus::InGame || room.get_nb_players() >= 4)
            continue;
        return room.add_player(player);
    }
    throw Room::RoomException("No room available.");
}

/**
 * @brief Join a specific room by its id. If room doesn't exists, throw exception
 *
 * @param player - Player &
 * @param room_id - std::size_t
 */
void rserver::game::RoomsManager::join_room(rserver::Player &player, const std::size_t &room_id)
{
    try {
        auto &room{this->get_room_by_id(room_id)};

        room.add_player(player);
    } catch (Room::RoomException &e) {
        throw e;
    }
}

/**
 * @brief Add a room to the list, and add the player that required this to the room
 *
 * @param first_player - Player &
 * @param nb_threads - size_t
 * @param socket - asio::udp::socket &
 */
void rserver::game::RoomsManager::add_room(rserver::Player &first_player,
                                           const std::size_t &nb_threads,
                                           asio::ip::udp::socket &socket)
{
    if (this->rooms.size() >= (nb_threads - 2))
        throw Room::RoomException("No room available.");
    this->rooms.emplace_back(socket, this->last_id);
    this->last_id++;
    try {
        this->rooms.back().add_player(first_player);
    } catch (Room::RoomException &e) {
        throw e;
    }
}

/**
 * @brief Make a player leave a room identified by its id
 *
 * @param player - Player &
 * @param room_id - size_t
 */
void rserver::game::RoomsManager::leave_room_with_id(rserver::Player &player,
                                                     const std::size_t &room_id)
{
    try {
        auto &room{this->get_room_by_id(room_id)};

        room.del_player(player);
    } catch (Room::RoomException &e) {
        throw e;
    }
}

/**
 * @brief Get a room by its id
 *
 * @param room_id - size_t
 */
rserver::game::Room &rserver::game::RoomsManager::get_room_by_id(const std::size_t &room_id)
{
    for (auto room{this->rooms.begin()}; room != this->rooms.end(); room++) {
        if (room->get_id() == room_id) {
            return *room;
        }
    }
    throw Room::RoomException("No room found with this id.");
}

/**
 * @brief Get all rooms
 *
 * @return vector<game::Room>
 */
std::vector<rserver::game::Room> &rserver::game::RoomsManager::get_rooms()
{
    return this->rooms;
}
