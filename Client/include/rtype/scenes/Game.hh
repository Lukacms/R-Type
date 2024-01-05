/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Game
*/

#pragma once

#include <asio.hpp>
#include <rtype/ECSManager.hpp>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/scenes/IScene.hh>
#include <rtype/utils/Clock.hh>

namespace rclient::scenes
{

    class Game : public IScene
    {
        public:
            Game(asio::ip::udp::endpoint &pendpoint, asio::ip::udp::socket &psocket);
            Game(Game const &to_copy) = delete;
            Game(Game &&to_move) = default;
            ~Game() override = default;
            Game &operator=(Game const &to_copy) = delete;
            Game &operator=(Game &&to_move) = delete;

            void display(rtype::GraphicModule &graphics) override;
            void handle_events(rtype::GraphicModule &graphics, sf::Event &events,
                               State &state) override;

        private:
            dl::DlLoader<rtype::ECSManager> ecs;
            rtype::utils::Clock timer_shoot{};

            /* to be able to send messages */
            asio::ip::udp::endpoint &endpoint;
            asio::ip::udp::socket &socket;
    };

} // namespace rclient::scenes
