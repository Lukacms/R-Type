/*
** EPITECH PROJECT, 2023
** commands
** File description:
** add_new_player
*/

#include <rtype.hh>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/Manager.hh>

void rserver::Manager::add_new_player(asio::ip::udp::endpoint &client)
{
    Player &new_player{this->players.add_player(client)};

    DEBUG(("New player with port: %d\n", new_player.get_port()));
}
