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
#include <rtype/PhysicsManager.hh>
#include <rtype/clients/PlayersManager.hh>
#include <shared_mutex>
#include <vector>

namespace rserver
{
    const constexpr int MAX_POSITION_X{900};
    const constexpr int MAX_POSITION_Y{700};
    const constexpr int MIN_POSITION{-200};
    constexpr double TIMER{0.01};

    class GameLogic
    {
        public:
            explicit GameLogic(asio::ip::udp::socket &socket, std::shared_mutex &ecs_mutex);
            GameLogic(GameLogic const &to_copy) = delete;
            GameLogic(GameLogic &&to_move) = delete;
            ~GameLogic() = default;

            GameLogic &operator=(GameLogic const &to_copy) = delete;
            GameLogic &operator=(GameLogic &&to_move) = delete;

            void game_loop(rtype::PhysicsManager &physics_manager,
                           rserver::PlayersManager &players_manager, rtype::ECSManager &manager,
                           float delta_time);
            void send_entity(rserver::PlayersManager &players_manager, rtype::ECSManager &manager);
            void destroy_too_far_entities(rserver::PlayersManager &players_manager,
                                          rtype::ECSManager &manager);
            void spawn_enemy(rtype::ECSManager &manager);

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
            std::chrono::time_point<std::chrono::steady_clock> m_start_enemy{
                std::chrono::steady_clock::now()};
    };
} // namespace rserver
