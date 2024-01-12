/*
** EPITECH PROJECT, 2023
** commands
** File description:
** lobby_handler
*/

#include <rtype/Manager.hh>

void rserver::Manager::lobby_handler()
{
    std::unique_lock<std::shared_mutex> lock{this->rooms_mutex};
    const auto &existing_rooms{this->rooms.get_rooms()};

    for (const auto &room : existing_rooms) {
        ntw::Communication commn{ntw::NetworkType::Room};

        commn.add_param(room.get_id());
        commn.add_param(room.get_nb_players());
        commn.add_param(static_cast<int>(room.get_status()));
        Manager::send_message(commn, this->players, this->udp_socket, PlayerStatus::Lobby);
    }
}
