/*
** EPITECH PROJECT, 2023
** commands
** File description:
** end_handler
*/

#include <iostream>
#include <rtype.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Manager.hh>

/**
 * @brief Command handler for Manager : end handler
 * Delete player from rooms
 *
 * @param player - Player &
 */
void rserver::Manager::end_handler(rserver::Player &player, std::vector<std::string> & /* args */)
{
    try {
        this->rooms.get_room_by_id(static_cast<std::size_t>(player.get_room_id()))
            .del_player(player);
        this->players.remove_player(player);
    } catch (PlayersManager::PlayersException &e) {
        DEBUG(("%s%s", e.what(), ENDL));
    } catch (game::Room::RoomException &e) {
        DEBUG(("%s%s", e.what(), ENDL));
    }
}
