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
void rserver::Manager::solo_handler(rserver::Player &player, std::vector<std::string> & /* args */)
{
    std::unique_lock<std::shared_mutex> lock{this->solos_mutex};

    try {
        if (player.get_room_id() != -1)
            throw game::solo::SoloGame::SoloException("Already in room");
        this->solos.emplace_back(this->udp_socket, player);
        Manager::send_message({ntw::NetworkType::ToGame}, player, this->udp_socket);
    } catch (game::solo::SoloGame::SoloException &e) {
        ntw::Communication commn{ntw::NetworkType::Ko};
        commn.add_param(e.what());
        DEBUG(("Exception occured when handling room: %s\n", e.what()));
        Manager::send_message(commn, player, this->udp_socket);
    }
}
