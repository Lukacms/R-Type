//
// Created by kane on 12/12/23.
//

#pragma once

#include <rtype/ECSManager.hpp>
#include <rtype/clients/PlayersManager.hh>
#include <asio.hpp>
#include <vector>

namespace rserver {
    class GameLogic {
        public:
            explicit GameLogic(asio::ip::udp::socket &socket);
            GameLogic(GameLogic const &to_copy) = default;
            GameLogic(GameLogic &&to_move) = default;
            ~GameLogic() = default;
            GameLogic &operator=(GameLogic const &to_copy) = delete;
            GameLogic &operator=(GameLogic &&to_move) = delete;

            void game_loop(rtype::ECSManager &manager, rserver::PlayersManager &players_manager);

            // Collisions responses
            void collision_responses(rtype::ECSManager &manager, rserver::PlayersManager &players_manager);
            void player_collision_responses(rtype::ECSManager &manager, rserver::PlayersManager &players_manager);
            void enemy_collision_responses(rtype::ECSManager &manager, rserver::PlayersManager &players_manager);

        private:
            std::vector<size_t> m_entities;
            asio::ip::udp::socket &m_socket;
    };
}
