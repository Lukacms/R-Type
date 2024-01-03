/*
** EPITECH PROJECT, 2023
** commands
** File description:
** room_handler
*/

#include <rtype.hh>
#include <rtype/Manager.hh>

void rserver::Manager::room_handler(rserver::Player &player, std::vector<std::string> &args)
{
    try {
        if (args.empty()) {
            this->rooms.add_room(player, this->threads.is_busy(), this->ecs_mutex,
                                 this->udp_socket);
        } else if (args.size() == 1 && is_number(args[1])) {
            this->rooms.join_room(player, get_number<std::size_t>(args[1]));
        } else {
            throw game::Room::RoomException("Wrong arguments.");
        }
    } catch (game::Room::RoomException &e) {
        ntw::Communication commn{ntw::NetworkType::Ko};
        commn.add_param(e.what());
        DEBUG(("Exception occured when creating room: %s\n", e.what()));
        Manager::send_message(commn, player, this->udp_socket);
    }
}
