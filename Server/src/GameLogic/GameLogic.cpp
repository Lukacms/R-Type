/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** GameLogic
*/

#include <rtype.hh>
#include <rtype/Components/ClockComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/Manager.hh>
#include <rtype/clients/PlayersManager.hh>
#include <rtype/utils/Vector2D.hpp>

static const std::array<rtype::utils::Vector2D<float>, 8> DIRECTIONS{{{0, -0.2F},
                                                                      {0.15F, -0.15F},
                                                                      {0.2F, 0},
                                                                      {0.15F, 0.15F},
                                                                      {0, 0.2F},
                                                                      {-0.15F, 0.15F},
                                                                      {-0.2F, 0},
                                                                      {-0.15F, -0.15F}}};

static const std::array<std::string, 5> ENEMIES{{
    {"BasicEnemy"},
    {"KamikazeEnemy"},
    {"UFOEnemy"},
    {"MineEnemy"},
    {"Asteroid"},
}};

/**
 * @brief Constructor
 *
 * @param socket - asio::udp::socket &
 * @param ecs_mutex - shared_mutex &
 */
rserver::game::GameLogic::GameLogic(asio::ip::udp::socket &socket, std::shared_mutex &ecs_mutex,
                                    const std::size_t &proom_id)
    : m_socket{socket}, m_ecs_mutex{ecs_mutex}, m_room_id{proom_id}
{
}

/**
 * @brief Constructor by move
 *
 * @param to_move - GameLogic && - object to move to current class
 */
rserver::game::GameLogic::GameLogic(rserver::game::GameLogic &&to_move)
    : m_socket{to_move.m_socket}, m_ecs_mutex{to_move.m_ecs_mutex}, m_room_id{to_move.m_room_id}
{
}

/**
 * @brief Game «loop». Do all actions needed by the game
 *
 * @param physics_manager - PhysicsManager &
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::game_loop(rtype::PhysicsManager &physics_manager,
                                         rserver::PlayersManager &players_manager,
                                         rtype::ECSManager &manager, float /* delta_time */)
{
    m_entities = manager.get_used_entity();

    physics_manager.check_collisions(manager);
    collision_responses(physics_manager, players_manager, manager);
    destroy_too_far_entities(players_manager, manager);
    destroy_too_long_entities(players_manager, manager);
    send_entity(players_manager, manager);
    check_if_player_out_of_bounds(manager);
    if (!m_level_manager.has_enough_level()) {
        spawn_enemy(manager);
        send_music(players_manager, STANDARD_MUSIC.data());
        send_background(players_manager, STANDARD_BACKGROUND.data());
        return;
    }
    m_level_manager.update(manager);
    send_music(players_manager, m_level_manager.get_current_music());
    send_background(players_manager, m_level_manager.get_current_background());
    if (m_level_manager.is_level_finished())
        m_level_manager.change_level();
}

/**
 * @brief Handle entities during room's waiting mode. Only move player, and allow it to shoot
 * bullets
 *
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 * @param delta_time - float
 */
void rserver::game::GameLogic::game_waiting(rserver::PlayersManager &players_manager,
                                            rtype::ECSManager &manager, float delta_time)
{
    m_entities = manager.get_used_entity();

    destroy_too_far_entities(players_manager, manager);
    send_entity(players_manager, manager);
    manager.apply_system(delta_time);
}

/**
 * @brief Get collisions and handle them
 *
 * @param physics_manager - PhysicsManager &
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::collision_responses(rtype::PhysicsManager &physics_manager,
                                                   rserver::PlayersManager &players_manager,
                                                   rtype::ECSManager &manager)
{
    player_collision_responses(physics_manager, players_manager, manager);
    enemy_collision_responses(physics_manager, players_manager, manager);
}

/**
 * @brief Handle collisions with the player
 *
 * @param physics_manager - PhysicsManager &
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
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
                if (entity1 == entity2 || !tags[entity2].has_value() ||
                    !physics_manager.is_collided(entity1, entity2))
                    continue;
                if (tags[entity2]->tag == "Upgrade" &&
                    physics_manager.is_collided(entity1, entity2)) {
                    players_manager.get_by_entity_room_id(entity1, m_room_id).level_up();
                    ntw::Communication destroy{.type = ntw::NetworkType::Destruction, .args = {}};
                    destroy.add_param(entity2);
                    rserver::Manager::send_message(destroy, players_manager, m_socket, m_room_id);
                    manager.delete_entity(entity2);
                }
                if (tags[entity2]->tag.find("Enemy") != std::string::npos ||
                    tags[entity2]->tag.find("Asteroid") != std::string::npos) {
                    at_player_death(manager, players_manager, entity1);
                }
            }
        }
    } catch (rtype::ECSManager::ECSException &e) {
        DEBUG(("Exception in player_collision_responses: %s%s", e.what(), ENDL));
    }
}

/**
 * @brief Handle collisions with enemies
 *
 * @param physics_manager - PhysicsManager &
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::enemy_collision_responses(rtype::PhysicsManager &physics_manager,
                                                         rserver::PlayersManager &players_manager,
                                                         rtype::ECSManager &manager)
{
    auto &tags{manager.get_components<rtype::TagComponent>()};
    auto &healths{manager.get_components<rtype::HealthComponent>()};

    for (const auto entity1 : m_entities) {
        if (!tags[entity1].has_value() || tags[entity1]->tag.find("Enemy") == std::string::npos)
            continue;
        for (const auto entity2 : m_entities) {
            if (!tags[entity1].has_value() || !healths[entity1].has_value() ||
                tags[entity2]->tag.find("Enemy") != std::string::npos || entity1 == entity2)
                continue;
            if (!physics_manager.is_collided(entity1, entity2))
                continue;
            if (tags[entity2]->tag.find("PlayerBullet") != std::string::npos) {
                healths[entity1]->health -= 10;
                check_if_enemy_dead(manager, players_manager, entity1);
                ntw::Communication destroy2{.type = ntw::NetworkType::Destruction, .args = {}};
                destroy2.add_param(entity2);
                rserver::Manager::send_message(destroy2, players_manager, m_socket, m_room_id);
                manager.delete_entity(entity2);
            }
            if (tags[entity2]->tag.find("Asteroid") != std::string::npos) {
                healths[entity1]->health = 0;
                check_if_enemy_dead(manager, players_manager, entity1);
            }
        }
    }
}

/**
 * @brief Send infos about all of the game's entities to players
 *
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::send_entity(rserver::PlayersManager &players_manager,
                                           rtype::ECSManager &manager)
{
    rtype::SparseArray<rtype::TransformComponent> &transforms{
        manager.get_components<rtype::TransformComponent>()};
    rtype::SparseArray<rtype::TagComponent> &tags{manager.get_components<rtype::TagComponent>()};

    for (size_t entity{0}; entity < transforms.size(); entity += 1) {
        ntw::Communication entity_descriptor{ntw::NetworkType::Entity, {}};
        if (!transforms[entity].has_value())
            continue;
        entity_descriptor.add_param(entity);
        entity_descriptor.add_param(!tags[entity].has_value() ? "Nothing" : tags[entity]->tag);
        entity_descriptor.add_param(transforms[entity]->position_x);
        entity_descriptor.add_param(transforms[entity]->position_y);
        entity_descriptor.add_param(transforms[entity]->rotation);
        Manager::send_message(entity_descriptor, players_manager, m_socket, m_room_id);
    }
}

/**
 * @brief Destroy entities that are not in screen's range
 *
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::destroy_too_far_entities(rserver::PlayersManager &players_manager,
                                                        rtype::ECSManager &manager)
{
    auto &transforms{manager.get_components<rtype::TransformComponent>()};
    auto &tag{manager.get_components<rtype::TagComponent>()};

    for (size_t entity{0}; entity < transforms.size(); entity += 1) {
        if (!transforms[entity].has_value())
            continue;
        if (!tag[entity].has_value())
            continue;
        if (tag[entity]->tag == "Player")
            continue;
        if (transforms[entity]->position_x < MIN_POSITION ||
            transforms[entity]->position_x > MAX_POSITION_X) {
            ntw::Communication send{.type = ntw::NetworkType::Destruction};
            manager.delete_entity(entity);
            send.add_param(entity);
            Manager::send_message(send, players_manager, m_socket, m_room_id);
        }
        if (transforms[entity]->position_y < MIN_POSITION ||
            transforms[entity]->position_y > MAX_POSITION_Y) {
            ntw::Communication send{.type = ntw::NetworkType::Destruction};
            manager.delete_entity(entity);
            send.add_param(entity);
            Manager::send_message(send, players_manager, m_socket, m_room_id);
        }
    }
}

/**
 * @brief Spawn enemy if enemies' clock is big enough
 *
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::spawn_enemy(rtype::ECSManager &manager)
{
    try {
        if (m_enemy_clock.get_elapsed_time_in_ms() > std::rand() % 1000 + 1000) {
            int turns = std::rand() % 4;
            for (; turns > 0; turns -= 1) {
                std::string random_enemy =
                    ENEMIES[static_cast<unsigned long>(std::rand()) % ENEMIES.size()];
                auto entity = rserver::ServerEntityFactory::create(random_enemy, manager);
                auto &transform = manager.get_component<rtype::TransformComponent>(entity);
                transform.position_y = std::rand() % 580;
                transform.velocity_x = -1.F * (static_cast<float>(std::rand() % 30) / 100 + 0.2F);
            }
            m_enemy_clock.reset();
        }
    } catch (rserver::ServerEntityFactory::FactoryException & /* e */) {
        return;
    }
}

/**
 * @brief Spawn bonus when a enemy is killed
 *
 * @param entity_to_follow - std::size_t - id of entity
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::spawn_at_enemy_death(std::size_t entity_to_follow, // NOLINT
                                                    rtype::ECSManager &manager)
{
    int success = std::rand() % 30;
    auto &transforms = manager.get_components<rtype::TransformComponent>();
    auto &tags = manager.get_components<rtype::TagComponent>();

    try {
        if (transforms[entity_to_follow].has_value() && success == 0) {
            std::size_t entity = rserver::ServerEntityFactory::create("Upgrade", manager);
            transforms[entity] = {transforms[entity_to_follow]};
            transforms[entity]->velocity_x = -0.1F;
            transforms[entity]->velocity_y = 0;
        }
        if (tags[entity_to_follow]->tag.find("Mine") != std::string::npos)
            spawn_bullets_for_mine(manager, entity_to_follow);
        size_t entity = rserver::ServerEntityFactory::create("Explosion", manager);
        auto &explosion = manager.get_component<rtype::TransformComponent>(entity);
        explosion = manager.get_component<rtype::TransformComponent>(entity_to_follow);
        explosion.velocity_x = 0;
        explosion.velocity_y = 0;
    } catch (rserver::ServerEntityFactory::FactoryException & /* e */) {
        return;
    }
}

/**
 * @brief Send music that is being played to all players
 *
 * @param players_manager - PlayersManager &
 * @param music_name - std::string - path to music
 */
void rserver::game::GameLogic::send_music(rserver::PlayersManager &players_manager,
                                          const std::string &music_name)
{
    if (music_name.empty())
        return;
    ntw::Communication music_descriptor{ntw::NetworkType::Music, {}};
    music_descriptor.add_param(music_name);
    Manager::send_message(music_descriptor, players_manager, m_socket, m_room_id);
}

void rserver::game::GameLogic::send_background(rserver::PlayersManager &players_manager,
                                               const std::string &background_name)
{
    if (background_name.empty())
        return;
    ntw::Communication background_descriptor{ntw::NetworkType::Background, {}};
    background_descriptor.add_param(background_name);
    Manager::send_message(background_descriptor, players_manager, m_socket, m_room_id);
}

/**
 * @brief Destroy entities that have a clock that has timed out
 *
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::destroy_too_long_entities(rserver::PlayersManager &players_manager,
                                                         rtype::ECSManager &manager)
{
    auto &tags = manager.get_components<rtype::TagComponent>();
    auto &clocks = manager.get_components<rtype::ClockComponent>();

    for (size_t entity{0}; entity < tags.size() && entity < clocks.size(); entity += 1) {
        ntw::Communication destruction_descriptor{ntw::NetworkType::Destruction, {}};
        if (!tags[entity].has_value() || !clocks[entity].has_value())
            continue;
        if (tags[entity]->tag == "Explosion" && clocks[entity]->clock.get_elapsed_time_in_s() > 2) {
            destruction_descriptor.add_param(entity);
            Manager::send_message(destruction_descriptor, players_manager, m_socket, m_room_id);
            manager.delete_entity(entity);
        }
    }
}

void rserver::game::GameLogic::check_if_player_out_of_bounds(rtype::ECSManager &manager)
{
    auto &transforms = manager.get_components<rtype::TransformComponent>();
    auto &tags = manager.get_components<rtype::TagComponent>();

    for (std::size_t entity = 0; entity < transforms.size() && entity < tags.size(); entity += 1) {
        if (!transforms[entity].has_value() || !tags[entity].has_value())
            continue;
        if (tags[entity]->tag != "Player")
            continue;
        auto &collider = manager.get_component<rtype::BoxColliderComponent>(entity);
        if (transforms[entity]->position_x > 800 - (collider.width * transforms[entity]->scale_x))
            transforms[entity]->position_x = 800 - (collider.width * transforms[entity]->scale_x);
        if (transforms[entity]->position_x < 0)
            transforms[entity]->position_x = 0;
        if (transforms[entity]->position_y > 600 - (collider.height * transforms[entity]->scale_y))
            transforms[entity]->position_y = 600 - (collider.height * transforms[entity]->scale_y);
        if (transforms[entity]->position_y < 0)
            transforms[entity]->position_y = 0;
    }
}

void rserver::game::GameLogic::check_if_enemy_dead(rtype::ECSManager &manager,
                                                   rserver::PlayersManager &players_manager,
                                                   std::size_t entity)
{
    auto &healths = manager.get_components<rtype::HealthComponent>();
    auto &tags = manager.get_components<rtype::TagComponent>();
    ntw::Communication destroy{.type = ntw::NetworkType::Destruction, .args = {}};

    if (!healths[entity].has_value() && !tags[entity].has_value())
        return;
    if (tags[entity]->tag.find("Enemy") == std::string::npos &&
        tags[entity]->tag.find("Player") == std::string::npos)
        return;
    if (healths[entity]->health > 0)
        return;
    destroy.add_param(entity);
    rserver::Manager::send_message(destroy, players_manager, m_socket, m_room_id);
    spawn_at_enemy_death(entity, manager);
    manager.delete_entity(entity);
}

void rserver::game::GameLogic::spawn_bullets_for_mine(rtype::ECSManager &manager,
                                                      std::size_t entity_to_follow)
{
    auto &follow_transform = manager.get_component<rtype::TransformComponent>(entity_to_follow);

    for (auto direction : DIRECTIONS) {
        std::size_t bullet = rserver::ServerEntityFactory::create("EnemyBullet", manager);
        auto &bullet_transform = manager.get_component<rtype::TransformComponent>(bullet);
        bullet_transform.position_x = follow_transform.position_x;
        bullet_transform.position_y = follow_transform.position_y;
        bullet_transform.velocity_x = direction.x;
        bullet_transform.velocity_y = direction.y;
    }
}

void rserver::game::GameLogic::at_player_death(rtype::ECSManager &manager,
                                               rserver::PlayersManager &players_manager,
                                               std::size_t player)
{
    ntw::Communication death{.type = ntw::NetworkType::End};
    ntw::Communication destruction{.type = ntw::NetworkType::Destruction};

    try {
        auto &p_network = players_manager.get_by_entity_room_id(player, m_room_id);

        destruction.add_param(player);
        rserver::Manager::send_message(death, p_network, m_socket);

        rserver::Manager::send_message(destruction, players_manager, m_socket, m_room_id);
        size_t entity = rserver::ServerEntityFactory::create("Explosion", manager);
        auto &explosion_transform = manager.get_component<rtype::TransformComponent>(entity);
        auto &player_transform = manager.get_component<rtype::TransformComponent>(player);
        explosion_transform.position_x = player_transform.position_x;
        explosion_transform.position_y = player_transform.position_y;
        manager.delete_entity(player);
    } catch (PlayersManager::PlayersException & /* e */) {
        return;
    }
}

void rserver::game::GameLogic::reset_clock()
{
    m_level_manager.reset_clock();
}

/* SOLO */

/**
 * @brief Game «loop». Do all actions needed by the game
 *
 * @param physics_manager - PhysicsManager &
 * @param players_manager - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::game_loop(rtype::PhysicsManager &physics_manager,
                                         rserver::Player &player, rtype::ECSManager &manager,
                                         float /* delta_time */)
{
    m_entities = manager.get_used_entity();

    physics_manager.check_collisions(manager);
    collision_responses(physics_manager, player, manager);
    destroy_too_far_entities(player, manager);
    destroy_too_long_entities(player, manager);
    send_entity(player, manager);
    check_if_player_out_of_bounds(manager);
    if (!m_level_manager.has_enough_level()) {
        spawn_enemy(manager);
        send_music(player, STANDARD_MUSIC.data());
        send_background(player, STANDARD_BACKGROUND.data());
        return;
    }
    m_level_manager.update(manager);
    send_music(player, m_level_manager.get_current_music());
    send_background(player, m_level_manager.get_current_background());
    if (m_level_manager.is_level_finished())
        m_level_manager.change_level();
}

/**
 * @brief Get collisions and handle them
 *
 * @param physics_manager - PhysicsManager &
 * @param player - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::collision_responses(rtype::PhysicsManager &physics_manager,
                                                   rserver::Player &player,
                                                   rtype::ECSManager &manager)
{
    try {
        player_collision_responses(physics_manager, player, manager);
    } catch (solo::SoloGame::SoloException &e) {
        throw e;
    }
    enemy_collision_responses(physics_manager, player, manager);
}

/**
 * @brief Handle collisions with the player
 *
 * @param physics_manager - PhysicsManager &
 * @param player - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::player_collision_responses( // NOLINT
    rtype::PhysicsManager &physics_manager, rserver::Player &player, rtype::ECSManager &manager)
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
                    player.level_up();
                    ntw::Communication destroy{.type = ntw::NetworkType::Destruction, .args = {}};
                    destroy.add_param(entity2);
                    rserver::Manager::send_message(destroy, player, m_socket);
                    manager.delete_entity(entity2);
                }
            }
        }
    } catch (rtype::ECSManager::ECSException &e) {
        DEBUG(("Exception in player_collision_responses: %s%s", e.what(), ENDL));
    }

    try {
        rtype::SparseArray<rtype::TagComponent> &tags =
            manager.get_components<rtype::TagComponent>();
        for (auto entity1 : m_entities) {
            if (!tags[entity1].has_value() || tags[entity1]->tag != "Player")
                continue;
            for (auto entity2 : m_entities) {
                if (entity1 == entity2 || !tags[entity2].has_value() ||
                    !physics_manager.is_collided(entity1, entity2))
                    continue;
                if (tags[entity2]->tag == "Upgrade" &&
                    physics_manager.is_collided(entity1, entity2)) {
                    player.level_up();
                    ntw::Communication destroy{.type = ntw::NetworkType::Destruction, .args = {}};
                    destroy.add_param(entity2);
                    rserver::Manager::send_message(destroy, player, m_socket);
                    manager.delete_entity(entity2);
                }
                if (tags[entity2]->tag.find("Enemy") != std::string::npos ||
                    tags[entity2]->tag.find("Asteroid") != std::string::npos) {
                    at_player_death(manager, player, entity1);
                    throw solo::SoloGame::SoloException("Death");
                }
            }
        }
    } catch (rtype::ECSManager::ECSException &e) {
        DEBUG(("Exception in player_collision_responses: %s%s", e.what(), ENDL));
    }
}

/**
 * @brief Handle collisions with enemies
 *
 * @param physics_manager - PhysicsManager &
 * @param player - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::enemy_collision_responses(rtype::PhysicsManager &physics_manager,
                                                         rserver::Player &player,
                                                         rtype::ECSManager &manager)
{
    auto &tags{manager.get_components<rtype::TagComponent>()};
    auto &healths{manager.get_components<rtype::HealthComponent>()};

    for (const auto entity1 : m_entities) {
        if (!tags[entity1].has_value() || tags[entity1]->tag.find("Enemy") == std::string::npos)
            continue;
        for (const auto entity2 : m_entities) {
            if (!tags[entity1].has_value() || !healths[entity1].has_value() ||
                tags[entity2]->tag.find("Enemy") != std::string::npos || entity1 == entity2)
                continue;
            if (!physics_manager.is_collided(entity1, entity2))
                continue;
            if (tags[entity2]->tag.find("PlayerBullet") != std::string::npos) {
                healths[entity1]->health -= 10;
                check_if_enemy_dead(manager, player, entity1);
                ntw::Communication destroy2{.type = ntw::NetworkType::Destruction, .args = {}};
                destroy2.add_param(entity2);
                rserver::Manager::send_message(destroy2, player, m_socket);
                manager.delete_entity(entity2);
            }
            if (tags[entity2]->tag.find("Asteroid") != std::string::npos) {
                healths[entity1]->health = 0;
                check_if_enemy_dead(manager, player, entity1);
            }
        }
    }
}

/**
 * @brief Send infos about all of the game's entities to players
 *
 * @param player - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::send_entity(rserver::Player &player, rtype::ECSManager &manager)
{
    rtype::SparseArray<rtype::TransformComponent> &transforms{
        manager.get_components<rtype::TransformComponent>()};
    rtype::SparseArray<rtype::TagComponent> &tags{manager.get_components<rtype::TagComponent>()};

    for (size_t entity{0}; entity < transforms.size(); entity += 1) {
        ntw::Communication entity_descriptor{ntw::NetworkType::Entity, {}};
        if (!transforms[entity].has_value())
            continue;
        entity_descriptor.add_param(entity);
        entity_descriptor.add_param(!tags[entity].has_value() ? "Nothing" : tags[entity]->tag);
        entity_descriptor.add_param(transforms[entity]->position_x);
        entity_descriptor.add_param(transforms[entity]->position_y);
        entity_descriptor.add_param(transforms[entity]->rotation);
        Manager::send_message(entity_descriptor, player, m_socket);
    }
}

/**
 * @brief Destroy entities that are not in screen's range
 *
 * @param player - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::destroy_too_far_entities(rserver::Player &player,
                                                        rtype::ECSManager &manager)
{
    auto &transforms{manager.get_components<rtype::TransformComponent>()};
    auto &tag{manager.get_components<rtype::TagComponent>()};

    for (size_t entity{0}; entity < transforms.size(); entity += 1) {
        if (!transforms[entity].has_value())
            continue;
        if (!tag[entity].has_value())
            continue;
        if (tag[entity]->tag == "Player")
            continue;
        if (transforms[entity]->position_x < MIN_POSITION ||
            transforms[entity]->position_x > MAX_POSITION_X) {
            ntw::Communication send{.type = ntw::NetworkType::Destruction};
            manager.delete_entity(entity);
            send.add_param(entity);
            Manager::send_message(send, player, m_socket);
        }
        if (transforms[entity]->position_y < MIN_POSITION ||
            transforms[entity]->position_y > MAX_POSITION_Y) {
            ntw::Communication send{.type = ntw::NetworkType::Destruction};
            manager.delete_entity(entity);
            send.add_param(entity);
            Manager::send_message(send, player, m_socket);
        }
    }
}

/**
 * @brief Send music that is being played to all players
 *
 * @param player - PlayersManager &
 * @param music_name - std::string - path to music
 */
void rserver::game::GameLogic::send_music(rserver::Player &player, const std::string &music_name)
{
    if (music_name.empty())
        return;
    ntw::Communication music_descriptor{ntw::NetworkType::Music, {}};
    music_descriptor.add_param(music_name);
    Manager::send_message(music_descriptor, player, m_socket);
}

/**
 * @brief Send background that is being played to all players
 *
 * @param player - PlayersManager &
 * @param music_name - std::string - path to music
 */
void rserver::game::GameLogic::send_background(rserver::Player &player,
                                               const std::string &background_name)
{
    if (background_name.empty())
        return;
    ntw::Communication background_descriptor{ntw::NetworkType::Background, {}};
    background_descriptor.add_param(background_name);
    Manager::send_message(background_descriptor, player, m_socket);
}

/**
 * @brief Destroy entities that have a clock that has timed out
 *
 * @param player - PlayersManager &
 * @param manager - ECSManager &
 */
void rserver::game::GameLogic::destroy_too_long_entities(rserver::Player &player,
                                                         rtype::ECSManager &manager)
{
    auto &tags = manager.get_components<rtype::TagComponent>();
    auto &clocks = manager.get_components<rtype::ClockComponent>();

    for (size_t entity{0}; entity < tags.size() && entity < clocks.size(); entity += 1) {
        ntw::Communication destruction_descriptor{ntw::NetworkType::Destruction, {}};
        if (!tags[entity].has_value() || !clocks[entity].has_value())
            continue;
        if (tags[entity]->tag == "Explosion" && clocks[entity]->clock.get_elapsed_time_in_s() > 2) {
            destruction_descriptor.add_param(entity);
            Manager::send_message(destruction_descriptor, player, m_socket);
            manager.delete_entity(entity);
        }
    }
}

void rserver::game::GameLogic::check_if_enemy_dead(rtype::ECSManager &manager,
                                                   rserver::Player &player, std::size_t entity)
{
    auto &healths = manager.get_components<rtype::HealthComponent>();
    auto &tags = manager.get_components<rtype::TagComponent>();
    ntw::Communication destroy{.type = ntw::NetworkType::Destruction, .args = {}};

    if (!healths[entity].has_value() && !tags[entity].has_value())
        return;
    if (tags[entity]->tag.find("Enemy") == std::string::npos &&
        tags[entity]->tag.find("Player") == std::string::npos)
        return;
    if (healths[entity]->health > 0)
        return;
    destroy.add_param(entity);
    rserver::Manager::send_message(destroy, player, m_socket);
    spawn_at_enemy_death(entity, manager);
    manager.delete_entity(entity);
}

void rserver::game::GameLogic::at_player_death(rtype::ECSManager &manager, rserver::Player &player,
                                               std::size_t entity)
{
    ntw::Communication death{.type = ntw::NetworkType::End};

    rserver::Manager::send_message(death, player, m_socket);
    manager.delete_entity(entity);
}
