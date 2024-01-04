/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** RoomsManager
*/

#include <rtype/GameLogic/RoomsManager.hh>

/* ctor / dtor */
rserver::game::RoomsManager::RoomsManager(rserver::PlayersManager &pmanager) : manager{pmanager}
{
}

rserver::game::RoomsManager::RoomsManager(rserver::game::RoomsManager &&to_move)
    : manager{to_move.manager}
{
}

/* methods */
void rserver::game::RoomsManager::join_random_room(rserver::Player &player)
{
    for (auto &room : this->rooms) {
        if (room.get_status() != RoomStatus::Waiting || room.get_nb_players() >= 4)
            continue;
        return room.add_player(player);
    }
    throw Room::RoomException("No room available.");
}

void rserver::game::RoomsManager::join_room(rserver::Player &player, const std::size_t &room_id)
{
    try {
        auto &room{this->get_room_by_id(room_id)};

        room.add_player(player);
    } catch (Room::RoomException &e) {
        throw e;
    }
}

void rserver::game::RoomsManager::add_room(rserver::Player &first_player,
                                           const std::size_t &nb_threads,
                                           asio::ip::udp::socket &socket)
{
    if (this->rooms.size() >= (nb_threads - 2))
        throw Room::RoomException("No room available.");
    auto &new_room{this->rooms.emplace_back(socket, this->manager, this->last_id)};
    this->last_id++;
    try {
        new_room.add_player(first_player);
    } catch (Room::RoomException &e) {
        throw e;
    }
}

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

rserver::game::Room &rserver::game::RoomsManager::get_room_by_id(const std::size_t &room_id)
{
    for (auto room{this->rooms.begin()}; room != this->rooms.end(); room++) {
        if (room->get_id() == room_id) {
            return *room;
        }
    }
    throw Room::RoomException("No room found with this id.");
}

std::vector<rserver::game::Room> &rserver::game::RoomsManager::get_rooms()
{
    return this->rooms;
}
