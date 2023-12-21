//
// Created by kane on 13/12/23.
//

#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/Manager.hh>
#include <rtype/clients/PlayersManager.hh>

rserver::GameLogic::GameLogic(asio::ip::udp::socket &socket) : m_socket{socket}
{
}

void rserver::GameLogic::game_loop(rtype::PhysicsManager &physics_manager,
                                   rserver::PlayersManager &players_manager,
                                   rtype::ECSManager &manager, float delta_time)
{
    collision_responses(physics_manager, players_manager, manager);
    {
        std::shared_lock<std::shared_mutex> lock{m_system_mutex};
        manager.apply_system(delta_time);
    }
    send_entity(players_manager, manager);
}

void rserver::GameLogic::collision_responses(rtype::PhysicsManager &physics_manager,
                                             rserver::PlayersManager &players_manager,
                                             rtype::ECSManager &manager)
{
    player_collision_responses(physics_manager, players_manager, manager);
    enemy_collision_responses(physics_manager, players_manager, manager);
}

void rserver::GameLogic::player_collision_responses(rtype::PhysicsManager &physics_manager,
                                                    rserver::PlayersManager &players_manager,
                                                    rtype::ECSManager &manager)
{
    SparseArray<rtype::TagComponent> &tags = manager.get_components<rtype::TagComponent>();

    for (auto entity1 : m_entities) {
        if (tags[entity1].has_value() || tags[entity1]->tag != "PLAYER")
            continue;
        for (auto entity2 : m_entities) {
            if (tags[entity2].has_value() || tags[entity2]->tag != "PLAYER" || entity1 == entity2)
                continue;
            if ((tags[entity2]->tag == "ENEMY" || tags[entity2]->tag == "ENEMY_PROJECTILE") &&
                physics_manager.is_collided(entity1, entity2)) {
                ntw::Communication com = {};
                manager.delete_entity(entity1);
                for (const auto &player : players_manager.get_all_players()) {
                    if (player.get_entity_value() == entity1) {
                        com.type = ntw::End;
                        rserver::Manager::send_message(com, player, m_socket);
                        continue;
                    }
                    com.type = ntw::Destruction;
                    com.add_param(entity1);
                    rserver::Manager::send_message(com, player, m_socket);
                }
                manager.delete_entity(entity1);
            }
            if (tags[entity2]->tag == "POWER_UP" && physics_manager.is_collided(entity1, entity2)) {
                // upgrade of player
            }
        }
    }
}

void rserver::GameLogic::enemy_collision_responses(rtype::PhysicsManager &physics_manager,
                                                   rserver::PlayersManager &players_manager,
                                                   rtype::ECSManager &manager)
{
    SparseArray<rtype::TagComponent> &tags = manager.get_components<rtype::TagComponent>();

    for (const auto entity1 : m_entities) {
        if (tags[entity1].has_value() || tags[entity1]->tag != "ENEMY")
            continue;
        for (const auto entity2 : m_entities) {
            if (tags[entity2].has_value() || tags[entity2]->tag != "ENEMY" || entity1 == entity2)
                continue;
            if (tags[entity2]->tag == "PLAYER_PROJECTILE" &&
                physics_manager.is_collided(entity1, entity2)) {
                ntw::Communication com = {};
                com.type = ntw::Destruction;
                com.args[0] = static_cast<char>(entity1);
                rserver::Manager::send_to_all(com, players_manager, m_socket);
                manager.delete_entity(entity1);
            }
        }
    }
}

void rserver::GameLogic::send_entity(rserver::PlayersManager &players_manager,
                                     rtype::ECSManager &manager)
{
    SparseArray<rtype::TransformComponent> &transforms =
        manager.get_components<rtype::TransformComponent>();
    SparseArray<rtype::TagComponent> &tags = manager.get_components<rtype::TagComponent>();

    for (size_t entity = 0; entity < transforms.size(); entity += 1) {
        ntw::Communication entity_descriptor{ntw::Entity, {}};
        if (!transforms[entity].has_value())
            continue;
        entity_descriptor.add_param(entity);
        entity_descriptor.add_param(!tags[entity].has_value() ? "NOTHING" : tags[entity]->tag);
        entity_descriptor.add_param(transforms[entity]->position_x);
        entity_descriptor.add_param(transforms[entity]->position_y);
        Manager::send_to_all(entity_descriptor, players_manager, m_socket);
    }
}
