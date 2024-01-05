/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#pragma once

#include <functional>
#include <memory>
#include <rtype/ComponentManager.hpp>
#include <rtype/ECSManager.hpp>
#include <rtype/Network/NetworkManager.hh>
#include <rtype/Network/ThreadPool.hh>
#include <rtype/config/ArgsConfig.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/scenes/Lounge.hh>
#include <rtype/scenes/Menu.hh>
#include <rtype/utils/Clock.hh>
#include <string_view>

namespace rclient
{

    constexpr int STANDARD_WIDTH{800};
    constexpr int STANDARD_HEIGHT{600};
    constexpr std::string_view STANDARD_TITLE{"R-TYPE"};
    constexpr double BULLET_TIMEOUT{250.0};
    constexpr double GAME_TIMEOUT{10.0};

    enum class State {
        Menu,
        Lounge,
        Game,
        Pause,
    };

    class Client
    {
        public:
            explicit Client(unsigned int &&width = STANDARD_WIDTH,
                            unsigned int &&height = STANDARD_HEIGHT,
                            const std::string &title = STANDARD_TITLE.data());
            ~Client();
            Client(const Client &) = delete;
            Client(Client &&) = delete;
            Client &operator=(const Client &) = delete;
            Client &operator=(Client &&) = delete;

            // static method to launch client
            static int launch(Arguments &infos);
            // Methods for running client
            int client_run();
            void client_menu();
            void client_game(rtype::utils::Clock &clock);
            void client_lounge(rtype::utils::Clock &clock);

            void set_network_infos(Arguments &infos);
            void configure_network();

            void check_input();

        private:
            dl::DlLoader<rtype::ECSManager> m_ecs;
            dl::DlLoader<rtype::GraphicModule> m_graphical_module;

            State m_state{State::Menu};
            scenes::Menu m_menu;
            scenes::Lounge m_lounge;

            std::chrono::time_point<std::chrono::steady_clock> m_timer_shoot;

            std::unique_ptr<rclient::NetworkManager> m_network{nullptr};
            ThreadPool threads{};
            std::string m_host;
            std::string m_port;
            std::deque<ntw::Communication> m_to_send{};
    };

    struct DisplayHandler {
        public:
            /* variables */
            State state{};
            std::function<void(Client &, rtype::utils::Clock &)> handler;
    };

} // namespace rclient
