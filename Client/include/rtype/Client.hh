/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <rtype/ComponentManager.hpp>
#include <rtype/ECSManager.hpp>
#include <rtype/GraphicModule.hh>
#include <rtype/Network/NetworkManager.hh>
#include <rtype/dlloader/DlLoader.hpp>

namespace rclient
{

    enum class STATE {
        Menu,
        Game,
    };

    const constexpr int STANDARD_WIDTH{800};
    const constexpr int STANDARD_HEIGHT{600};
    const constexpr char *STANDARD_TITLE{"R-TYPE"};

    class Client
    {
        public:
            explicit Client(unsigned int width = STANDARD_WIDTH, unsigned int height = STANDARD_HEIGHT,
                   const std::string &title = STANDARD_TITLE);
            ~Client() = default;
            Client(const Client &) = delete;
            Client(Client &&) = delete;
            Client &operator=(const Client &) = delete;
            Client &operator=(Client &&) = delete;

            // Methods for running client
            int client_run();
            void client_menu();
            void client_game();

            void configure_network();

        private:
            dl::DlLoader<rtype::ECSManager> m_ecs;
            dl::DlLoader<rtype::GraphicModule> m_graphical_module;
            STATE m_state{STATE::Menu};
            std::unique_ptr<NetworkManager> m_network{nullptr};
            std::string m_host;
            std::string m_port;
    };
} // namespace rclient
