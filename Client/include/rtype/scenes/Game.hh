/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Game
*/

#pragma once

#include <asio.hpp>
#include <functional>
#include <rtype/Background/BackgroundManager.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/scenes/IScene.hh>
#include <rtype/utils/Clock.hh>
#include <shared_mutex>

namespace rclient::scenes
{

    /**
     * @class Game
     * @brief Game Scene. Is a child of IScene
     *
     */
    class Game : public IScene
    {
        public:
            Game(asio::ip::udp::endpoint &pendpoint, asio::ip::udp::socket &psocket);
            Game(Game const &to_copy) = delete;
            Game(Game &&to_move) = delete;
            ~Game() override = default;
            Game &operator=(Game const &to_copy) = delete;
            Game &operator=(Game &&to_move) = delete;

            void display(rtype::IGraphicModule &graphics) override;
            void handle_events(rtype::IGraphicModule &graphics, rtype::IAudioModule &audio,
                               State &state) override;
            void handle_network(ntw::Communication &commn, rtype::IAudioModule &audio,
                                State &state) override;

            /* network */
            void create_entity(ntw::Communication &commn, State &state);
            void move_entity(ntw::Communication &commn, State &state);
            void end_game(ntw::Communication &commn, State &state);
            void delete_entity(ntw::Communication &commn, State &state);
            void manage_entity(ntw::Communication &commn, State &state);
            void change_music(ntw::Communication &commn, rtype::IAudioModule &audio);
            void change_background(ntw::Communication commn);

        private:
            dl::DlLoader<rtype::ECSManager> ecs;
            std::shared_mutex ecs_mutex{};
            rtype::utils::Clock timer_shoot{};

            /* to be able to send messages */
            asio::ip::udp::endpoint &endpoint;
            asio::ip::udp::socket &socket;

            rclient::BackgroundManager background_manager{};
    };

    struct CommandHandler {
            ntw::NetworkType type;
            std::function<void(rclient::scenes::Game &, ntw::Communication &, State &state)>
                handler;
    };

} // namespace rclient::scenes
