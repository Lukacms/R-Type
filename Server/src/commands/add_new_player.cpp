/*
** EPITECH PROJECT, 2023
** commands
** File description:
** add_new_player
*/

#include <rtype.hh>
#include <rtype/Manager.hh>
#include <rtype/Factory/ServerEntityFactory.hh>

void rserver::Manager::add_new_player(asio::ip::udp::endpoint &client)
{
    Player &new_player{this->players.add_player(client, this->udp_socket)};

    new_player.set_entity_value(rserver::ServerEntityFactory::create("Player", this->ecs.get_class()));
    DEBUG(("New player with port: %d\n", new_player.get_port()));
}
