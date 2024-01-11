/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** GameLogic
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <rtype/ECSManager.hpp>
#include <rtype/GameLogic/LevelManager/LevelManager.hh>
#include <rtype/PhysicsManager.hh>
#include <rtype/clients/PlayersManager.hh>
#include <rtype/utils/Clock.hh>
#include <shared_mutex>
#include <vector>

namespace rserver::game
{
    const constexpr int MAX_POSITION_X{900};
    const constexpr int MAX_POSITION_Y{700};
    const constexpr int MIN_POSITION{-200};
    constexpr double TIMER{10};
    constexpr std::string_view STANDARD_MUSIC{"Voyage1970"};

    void kamikaze_system(rtype::ComponentManager &registry, float /* delta_time */);
    void ufo_system(rtype::ComponentManager &registry, float /* delta_time */);

    class GameLogic
    {
        public:
            explicit GameLogic(asio::ip::udp::socket &socket, std::shared_mutex &ecs_mutex);
            GameLogic(GameLogic const &to_copy) = delete;
            GameLogic(GameLogic &&to_move);
            ~GameLogic() = default;

            GameLogic &operator=(GameLogic const &to_copy) = delete;
            GameLogic &operator=(GameLogic &&to_move) = delete;

            void game_loop(rtype::PhysicsManager &physics_manager,
                           rserver::PlayersManager &players_manager, rtype::ECSManager &manager,
                           float delta_time);
            void game_waiting(rserver::PlayersManager &players_manager, rtype::ECSManager &manager,
                              float delta_time);
            void send_entity(rserver::PlayersManager &players_manager, rtype::ECSManager &manager);
            void send_music(rserver::PlayersManager &players_manager,
                            const std::string &music_name);
            void destroy_too_far_entities(rserver::PlayersManager &players_manager,
                                          rtype::ECSManager &manager);
            void destroy_too_long_entities(rserver::PlayersManager &players_manager,
                                           rtype::ECSManager &manager);
            void spawn_enemy(rtype::ECSManager &manager);
            void spawn_at_enemy_death(std::size_t entity_to_follow, rtype::ECSManager &manager);

            // Collisions responses
            void collision_responses(rtype::PhysicsManager &physics_manager,
                                     rserver::PlayersManager &players_manager,
                                     rtype::ECSManager &manager);
            void player_collision_responses(rtype::PhysicsManager &physics_manager,
                                            rserver::PlayersManager &players_manager,
                                            rtype::ECSManager &manager);
            void enemy_collision_responses(rtype::PhysicsManager &physics_manager,
                                           rserver::PlayersManager &players_manager,
                                           rtype::ECSManager &manager);

        private:
            std::vector<size_t> m_entities{};
            asio::ip::udp::socket &m_socket;
            std::shared_mutex &m_ecs_mutex;
            rtype::utils::Clock m_enemy_clock{};
            rserver::LevelManager m_level_manager{};
            rtype::utils::Clock m_clock{};
    };
} // namespace rserver::game
