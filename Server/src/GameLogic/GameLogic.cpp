/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** GameLogic
*/

#include <rtype.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/Manager.hh>
#include <rtype/clients/PlayersManager.hh>

rserver::game::GameLogic::GameLogic(asio::ip::udp::socket &socket, std::shared_mutex &ecs_mutex)
    : m_socket{socket}, m_ecs_mutex{ecs_mutex}
{
}

rserver::game::GameLogic::GameLogic(rserver::game::GameLogic &&to_move)
    : m_socket{to_move.m_socket}, m_ecs_mutex{to_move.m_ecs_mutex}
{
}

void rserver::game::GameLogic::game_loop(rtype::PhysicsManager &physics_manager,
                                         rserver::PlayersManager &players_manager,
                                         rtype::ECSManager &manager, float /* delta_time */)
{
    m_entities = manager.get_used_entity();

    physics_manager.check_collisions(manager);
    collision_responses(physics_manager, players_manager, manager);
    destroy_too_far_entities(players_manager, manager);
    send_entity(players_manager, manager);
    spawn_enemy(manager);
}

void rserver::game::GameLogic::collision_responses(rtype::PhysicsManager &physics_manager,
                                                   rserver::PlayersManager &players_manager,
                                                   rtype::ECSManager &manager)
{
    player_collision_responses(physics_manager, players_manager, manager);
    enemy_collision_responses(physics_manager, players_manager, manager);
}

void rserver::game::GameLogic::player_collision_responses(rtype::PhysicsManager &physics_manager,
                                                          rserver::PlayersManager &players_manager,
                                                          rtype::ECSManager &manager)
{
    try {
        rtype::SparseArray<rtype::TagComponent> &tags =
            manager.get_components<rtype::TagComponent>();
        for (auto entity1 : m_entities) {
            if (!tags[entity1].has_value() || tags[entity1]->tag != "Player")
                continue;
            for (auto entity2 : m_entities) {
                if (entity1 == entity2 || !tags[entity2].has_value())
                    continue;
                if (tags[entity2]->tag == "Upgrade" &&
                    physics_manager.is_collided(entity1, entity2)) {
                    players_manager.get_by_entity_id(entity1).level_up();
                    ntw::Communication destroy{.type = ntw::NetworkType::Destruction, .args = {}};
                    destroy.add_param(entity2);
                    rserver::Manager::send_to_all(destroy, players_manager, m_socket);
                    manager.delete_entity(entity2);
                }
            }
        }
    } catch (rtype::ECSManager::ECSException &e) {
        DEBUG(("Exception in player_collision_responses: %s%s", e.what(), ENDL));
    }
}

void rserver::game::GameLogic::enemy_collision_responses(rtype::PhysicsManager &physics_manager,
                                                         rserver::PlayersManager &players_manager,
                                                         rtype::ECSManager &manager)
{
    rtype::SparseArray<rtype::TagComponent> &tags = manager.get_components<rtype::TagComponent>();

    for (const auto entity1 : m_entities) {
        if (!tags[entity1].has_value() || tags[entity1]->tag.find("Enemy") == std::string::npos)
            continue;
        for (const auto entity2 : m_entities) {
            if (!tags[entity1].has_value() ||
                tags[entity2]->tag.find("Enemy") != std::string::npos || entity1 == entity2)
                continue;
            if (tags[entity2]->tag.find("Bullet") != std::string::npos &&
                physics_manager.is_collided(entity1, entity2)) {
                ntw::Communication destroy1{.type = ntw::NetworkType::Destruction, .args = {}};
                destroy1.add_param(entity1);
                ntw::Communication destroy2{.type = ntw::NetworkType::Destruction, .args = {}};
                destroy2.add_param(entity2);
                rserver::Manager::send_to_all(destroy1, players_manager, m_socket);
                rserver::Manager::send_to_all(destroy2, players_manager, m_socket);
                spawn_upgrade(entity1, manager);
                manager.delete_entity(entity1);
                manager.delete_entity(entity2);
            }
        }
    }
}

void rserver::game::GameLogic::send_entity(rserver::PlayersManager &players_manager,
                                           rtype::ECSManager &manager)
{
    rtype::SparseArray<rtype::TransformComponent> &transforms =
        manager.get_components<rtype::TransformComponent>();
    rtype::SparseArray<rtype::TagComponent> &tags = manager.get_components<rtype::TagComponent>();

    for (size_t entity = 0; entity < transforms.size(); entity += 1) {
        ntw::Communication entity_descriptor{ntw::NetworkType::Entity, {}};
        if (!transforms[entity].has_value())
            continue;
        entity_descriptor.add_param(entity);
        entity_descriptor.add_param(!tags[entity].has_value() ? "Nothing" : tags[entity]->tag);
        entity_descriptor.add_param(transforms[entity]->position_x);
        entity_descriptor.add_param(transforms[entity]->position_y);
        Manager::send_to_all(entity_descriptor, players_manager, m_socket);
    }
}

void rserver::game::GameLogic::destroy_too_far_entities(rserver::PlayersManager &players_manager,
                                                        rtype::ECSManager &manager)
{
    auto &transforms = manager.get_components<rtype::TransformComponent>();
    auto &tag = manager.get_components<rtype::TagComponent>();

    for (size_t entity = 0; entity < transforms.size(); entity += 1) {
        if (!transforms[entity].has_value())
            continue;
        if (!tag[entity].has_value())
            continue;
        if (tag[entity]->tag.find("Enemy") == std::string::npos &&
            tag[entity]->tag.find("Bullet") == std::string::npos)
            continue;
        if (transforms[entity]->position_x < MIN_POSITION ||
            transforms[entity]->position_x > MAX_POSITION_X) {
            ntw::Communication send{.type = ntw::NetworkType::Destruction, .args = {}};
            manager.delete_entity(entity);
            send.add_param(entity);
            Manager::send_to_all(send, players_manager, m_socket);
        }
        if (transforms[entity]->position_y < MIN_POSITION ||
            transforms[entity]->position_y > MAX_POSITION_Y) {
            ntw::Communication send{.type = ntw::NetworkType::Destruction, .args = {}};
            manager.delete_entity(entity);
            send.add_param(entity);
            Manager::send_to_all(send, players_manager, m_socket);
        }
    }
}

void rserver::game::GameLogic::spawn_enemy(rtype::ECSManager &manager)
{
    auto update = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::seconds>(update - m_start_enemy).count() > 2) {
        std::shared_lock<std::shared_mutex> lock{m_ecs_mutex};
        rserver::ServerEntityFactory::create("BasicEnemy", manager);
        m_start_enemy = update;
    }
}

void rserver::game::GameLogic::spawn_upgrade(std::size_t entity_to_follow,
                                             rtype::ECSManager &manager)
{
    int success = std::rand() % 10;
    auto &transforms = manager.get_components<rtype::TransformComponent>();

    if (transforms[entity_to_follow].has_value()) {
        std::shared_lock<std::shared_mutex> lock{m_ecs_mutex};
        std::size_t entity = rserver::ServerEntityFactory::create("Upgrade", manager);
        transforms[entity] = {transforms[entity_to_follow]};
    }
}
