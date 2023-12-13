//
// Created by kane on 13/12/23.
//

#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/clients/PlayersManager.hh>
#include <rtype/Manager.hh>

rserver::GameLogic::GameLogic(asio::ip::udp::socket &socket) : m_socket{socket} {}

void rserver::GameLogic::game_loop(rtype::ECSManager &manager, rserver::PlayersManager &players_manager)
{
    collision_responses(manager, players_manager);
}

void rserver::GameLogic::collision_responses(rtype::ECSManager &manager, rserver::PlayersManager &players_manager)
{
    player_collision_responses(manager, players_manager);
    enemy_collision_responses(manager, players_manager);
}

void rserver::GameLogic::player_collision_responses(rtype::ECSManager &manager, rserver::PlayersManager &players_manager)
{
    SparseArray<rtype::TagComponent> &tags = manager.get_components<rtype::TagComponent>();

    for (auto entity1 : m_entities) {
        if (tags[entity1].has_value() || tags[entity1]->tag != "PLAYER")
            continue;
        for (auto entity2 : m_entities) {
            if (tags[entity2].has_value() || tags[entity2]->tag != "PLAYER" || entity1 == entity2)
                continue;
            if ((tags[entity2]->tag == "ENEMY" || tags[entity2]->tag == "ENEMY_PROJECTILE") &&
                manager.is_collided(entity1, entity2)) {
                for (const auto &player : players_manager.get_all_players()) {
                    if (player.get_entity_value() == entity1) {
                        // Send END of the game;
                        // rserver::Manager::send_message(/*command*/ , c, m_socket);
                        continue;
                    }
                    // Send destroy of an entity;
                    // rserver::Manager::send_message(/*command*/ , c, m_socket);
                }
                manager.delete_entity(entity1);
            }
            if (tags[entity2]->tag == "POWER_UP" && manager.is_collided(entity1, entity2)) {
                // upgrade of player
            }
        }
    }
}

void rserver::GameLogic::enemy_collision_responses(rtype::ECSManager &manager, rserver::PlayersManager &players_manager)
{
    SparseArray<rtype::TagComponent> &tags = manager.get_components<rtype::TagComponent>();

    for (const auto entity1 : m_entities) {
        if (tags[entity1].has_value() || tags[entity1]->tag != "ENEMY")
            continue;
        for (const auto entity2 : m_entities) {
            if (tags[entity2].has_value() || tags[entity2]->tag != "ENEMY" || entity1 == entity2)
                continue;
            if (tags[entity2]->tag == "PLAYER_PROJECTILE" &&
                manager.is_collided(entity1, entity2)) {
                // Send message of the death of enemy :x
                manager.delete_entity(entity1);
            }
        }
    }
}
