/*
** EPITECH PROJECT, 2023
** commands
** File description:
** room_handler
*/

#include <rtype.hh>
#include <rtype/Manager.hh>

/**
 * @brief Handle room command from player
 *
 * @param player - Player &
 * @param args - vector<string> &
 */
void rserver::Manager::room_handler(rserver::Player &player, std::vector<std::string> &args)
{
    try {
        if (args.empty()) {
            this->rooms.add_room(player, this->threads.is_busy(), this->udp_socket, this->players);
            Manager::send_message({ntw::NetworkType::ToGame}, player, this->udp_socket);
            return;
        }
        if (args.size() == 1 && is_number(args[0])) {
            this->rooms.join_room(player, get_number<std::size_t>(args[0]));
            Manager::send_message({ntw::NetworkType::ToGame}, player, this->udp_socket);
            return;
        }
        if (args.size() == 1 && get_number<int>(args[0]) == -1) {
            this->rooms.join_random_room(player);
            Manager::send_message({ntw::NetworkType::ToGame}, player, this->udp_socket);
            return;
        }
        throw game::Room::RoomException("Wrong arguments.");
    } catch (game::Room::RoomException &e) {
        ntw::Communication commn{ntw::NetworkType::Ko};
        commn.add_param(e.what());
        DEBUG(("Exception occured when handling room: %s\n", e.what()));
        Manager::send_message(commn, player, this->udp_socket);
    }
}
