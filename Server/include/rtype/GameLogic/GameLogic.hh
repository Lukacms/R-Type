//
// Created by kane on 12/12/23.
//

#pragma once

#include <asio.hpp>
#include <rtype/ECSManager.hpp>
#include <rtype/PhysicsManager.hh>
#include <rtype/clients/PlayersManager.hh>
#include <vector>

namespace rserver
{
    class GameLogic
    {
        public:
            explicit GameLogic(asio::ip::udp::socket &socket);
            GameLogic(GameLogic const &to_copy) = default;
            GameLogic(GameLogic &&to_move) = default;
            ~GameLogic() = default;

            GameLogic &operator=(GameLogic const &to_copy) = delete;
            GameLogic &operator=(GameLogic &&to_move) = delete;

            void game_loop(rtype::PhysicsManager &physics_manager,
                           rserver::PlayersManager &players_manager, rtype::ECSManager &manager);
            void send_entity(rserver::PlayersManager &players_manager, rtype::ECSManager &manager);

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
    };
} // namespace rserver
