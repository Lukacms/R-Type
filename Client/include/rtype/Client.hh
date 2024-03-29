/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Client
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the client core
#define ASIO_HEADER_ONLY

#include <algorithm>
#include <asio.hpp>
#include <memory>
#include <rtype/ComponentManager.hpp>
#include <rtype/ECSManager.hpp>
#include <rtype/IAudioModule.hh>
#include <rtype/IGraphicModule.hh>
#include <rtype/config/ArgsConfig.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/network/Network.hpp>
#include <rtype/scenes/Game.hh>
#include <rtype/scenes/Lounge.hh>
#include <rtype/scenes/Menu.hh>
#include <rtype/scenes/PauseMenu.hh>
#include <rtype/utils/Clock.hh>
#include <rtype/utils/ThreadPool.hh>
#include <string>
#include <string_view>

namespace rclient
{

    constexpr std::string_view STANDARD_TITLE{"R-TYPE"};
    constexpr double BULLET_TIMEOUT{250.0};
    constexpr double GAME_TIMEOUT{10.0};

    class Client
    {
        public:
            Client(const rclient::Arguments &infos);
            Client(Client const &to_copy) = delete;
            Client(Client &&to_move);
            ~Client();
            Client &operator=(Client const &to_copy) = delete;
            Client &operator=(Client &&to_move) = delete;

            /* methods */
            static int launch(const Arguments &infos);

            static void send_message(const ntw::Communication &commn,
                                     const asio::ip::udp::endpoint &endpoint,
                                     asio::ip::udp::socket &socket);
            void loop();

            class ClientException : std::exception
            {
                public:
                    ClientException(std::string &&perror_msg);
                    ClientException(ClientException const &to_copy) = default;
                    ClientException(ClientException &&to_move) = default;
                    ~ClientException() override = default;
                    ClientException &operator=(ClientException const &to_copy) = default;
                    ClientException &operator=(ClientException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string m_error_msg{"Error"};
            };

        private:
            /* game engine */
            dl::DlLoader<rtype::IGraphicModule> graphics;
            dl::DlLoader<rtype::IAudioModule> audio;

            std::shared_mutex graphics_lock{};
            std::shared_mutex audio_lock{};

            /* network */
            asio::io_context context{};
            asio::ip::udp::resolver resolver;
            asio::ip::udp::endpoint endpoint{};
            asio::ip::udp::socket socket;

            /* utils for graphics */
            scenes::State state{scenes::State::Menu};
            scenes::Menu menu{};
            scenes::Lounge lounge;
            scenes::PauseMenu pause{};
            scenes::Game game;
            std::shared_mutex scenes;

            /* utils for network */
            rtype::utils::ThreadPool threads{};
            std::string host{};
            std::string port{};

            /* methods */
            void setup_network();
            void launch_displays();
            void check_events();
    };

} // namespace rclient
