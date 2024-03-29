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
    constexpr std::string_view STANDARD_MUSIC{"SeptetteForTheDeadPrincess"};
    constexpr std::string_view STANDARD_BACKGROUND{"DeepPurpleNebula"};

    void kamikaze_system(rtype::ComponentManager &registry, float /* delta_time */);
    void ufo_system(rtype::ComponentManager &registry, float /* delta_time */);

    /**
     * @class GameLogic
     * @brief To handle a game. Create entities with the ECS, move them when needed, launch level,
     * waves of enemies, ...
     *
     */
    class GameLogic
    {
        public:
            GameLogic(asio::ip::udp::socket &socket, std::shared_mutex &ecs_mutex,
                      const std::size_t &proom_id);
            GameLogic(GameLogic const &to_copy) = delete;
            GameLogic(GameLogic &&to_move);
            ~GameLogic() = default;

            GameLogic &operator=(GameLogic const &to_copy) = delete;
            GameLogic &operator=(GameLogic &&to_move) = delete;

            /* multi game */
            void game_loop(rtype::PhysicsManager &physics_manager,
                           rserver::PlayersManager &players_manager, rtype::ECSManager &manager,
                           float delta_time);
            void game_waiting(rserver::PlayersManager &players_manager, rtype::ECSManager &manager,
                              float delta_time);
            void send_entity(rserver::PlayersManager &players_manager, rtype::ECSManager &manager);
            void send_music(rserver::PlayersManager &players_manager,
                            const std::string &music_name);
            void send_background(rserver::PlayersManager &players_manager,
                                 const std::string &background_name);
            void destroy_too_far_entities(rserver::PlayersManager &players_manager,
                                          rtype::ECSManager &manager);
            void destroy_too_long_entities(rserver::PlayersManager &players_manager,
                                           rtype::ECSManager &manager);
            void spawn_enemy(rtype::ECSManager &manager);
            void spawn_at_enemy_death(std::size_t entity_to_follow, rtype::ECSManager &manager);
            static void spawn_bullets_for_mine(rtype::ECSManager &manager,
                                               std::size_t entity_to_follow);
            void at_player_death(rtype::ECSManager &manager,
                                 rserver::PlayersManager &players_manager, std::size_t player);

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

            void check_if_player_out_of_bounds(rtype::ECSManager &manager);
            void check_if_enemy_dead(rtype::ECSManager &manager,
                                     rserver::PlayersManager &players_manager, std::size_t entity);
            void reset_clock();

            /* solo game */
            void game_loop(rtype::PhysicsManager &physics_manager, rserver::Player &player,
                           rtype::ECSManager &manager, float delta_time);
            void send_entity(rserver::Player &player, rtype::ECSManager &manager);
            void send_music(rserver::Player &player, const std::string &music_name);
            void send_background(rserver::Player &player, const std::string &background_name);
            void destroy_too_far_entities(rserver::Player &player, rtype::ECSManager &manager);
            void destroy_too_long_entities(rserver::Player &player, rtype::ECSManager &manager);
            void check_if_enemy_dead(rtype::ECSManager &manager, rserver::Player &player,
                                     std::size_t entity);
            void at_player_death(rtype::ECSManager &manager, rserver::Player &player,
                                 std::size_t entity);

            // Collisions responses
            void collision_responses(rtype::PhysicsManager &physics_manager,
                                     rserver::Player &player, rtype::ECSManager &manager);
            void player_collision_responses(rtype::PhysicsManager &physics_manager,
                                            rserver::Player &player, rtype::ECSManager &manager);
            void enemy_collision_responses(rtype::PhysicsManager &physics_manager,
                                           rserver::Player &player, rtype::ECSManager &manager);

        private:
            std::vector<size_t> m_entities{};
            asio::ip::udp::socket &m_socket;
            std::shared_mutex &m_ecs_mutex;
            rtype::utils::Clock m_enemy_clock{};
            rserver::LevelManager m_level_manager{};
            rtype::utils::Clock m_clock{};
            std::size_t m_room_id{};
    };
} // namespace rserver::game
