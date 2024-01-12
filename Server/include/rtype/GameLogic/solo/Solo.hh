/*
** EPITECH PROJECT, 2023
** solo
** File description:
** Solo
*/

#pragma once

#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/GameLogic/solo/Friend.hh>
#include <rtype/clients/Player.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <shared_mutex>

namespace rserver::game::solo
{

    class SoloGame
    {
        public:
            SoloGame(asio::ip::udp::socket &psocket, asio::ip::udp::endpoint &pendpoint);
            SoloGame(SoloGame const &to_copy) = delete;
            SoloGame(SoloGame &&to_move);
            ~SoloGame() = default;
            SoloGame &operator=(SoloGame const &to_copy) = delete;
            SoloGame &operator=(SoloGame &&to_move);

        private:
            GameLogic game;
            Player player;
            dl::DlLoader<rtype::ECSManager> ecs{};
            std::vector<Friend> ai{};

            asio::ip::udp::socket &socket;
            std::shared_mutex ecs_mutex;
    };

} // namespace rserver::game::solo
