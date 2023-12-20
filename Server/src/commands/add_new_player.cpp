/*
** EPITECH PROJECT, 2023
** commands
** File description:
** add_new_player
*/

#include <rtype.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Manager.hh>

void rserver::Manager::add_new_player(asio::ip::udp::endpoint &client)
{
    Player &new_player{this->players.add_player(client, this->udp_socket)};

    new_player.set_entity_value(this->ecs.get_class().create_entity());
    auto &transform{this->ecs.get_class().get_components<rtype::TransformComponent>()};
    auto &boxes{this->ecs.get_class().get_components<rtype::BoxColliderComponent>()};
    auto &tags{this->ecs.get_class().get_components<rtype::TagComponent>()};
    auto &healths{this->ecs.get_class().get_components<rtype::HealthComponent>()};

    tags.insert_at(new_player.get_entity_value(), {.tag = "Player"});
    transform.insert_at(new_player.get_entity_value(), {50, 250, 0, 0, 2, 2});
    boxes.insert_at(new_player.get_entity_value(), {});
    healths.insert_at(new_player.get_entity_value(), {});
    DEBUG(("New player with port: %d\n", new_player.get_port()));
}
