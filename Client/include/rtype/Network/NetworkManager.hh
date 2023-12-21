/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the client core
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <deque>
#include <rtype/ECSManager.hpp>
#include <rtype/network/Network.hpp>

using asio::ip::udp;

namespace rclient
{

    class NetworkManager
    {
        public:
            NetworkManager(const std::string &host, const std::string &port);
            ~NetworkManager() = default;
            NetworkManager(NetworkManager const &other) = delete;
            NetworkManager(NetworkManager &&other) = delete;
            NetworkManager &operator=(NetworkManager const &other) = delete;
            NetworkManager &operator=(NetworkManager &&other) = delete;

            void fetch_messages();
            void send_message(ntw::Communication &communication);
            void manage_message(rtype::ECSManager &manager);
            void handle_receive(const asio::error_code &error, std::size_t bytes_transferre);

            [[nodiscard]] std::deque<ntw::Communication> &get_message_queue();

            // In order to have a pointer on these functions
            static void create_entity(NetworkManager &network_manager,
                                      rtype::ECSManager &ecs_manager,
                                      ntw::Communication &communication);
            static void move_entity(NetworkManager &network_manager, rtype::ECSManager &ecs_manager,
                                    ntw::Communication &communication);
            static void end_game(NetworkManager &network_manager, rtype::ECSManager &ecs_manager,
                                 ntw::Communication &communication);
            static void delete_entity(NetworkManager &network_manager,
                                      rtype::ECSManager &ecs_manager,
                                      ntw::Communication &communication);
            static void manage_entity(NetworkManager &network_manager,
                                      rtype::ECSManager &ecs_manager,
                                      ntw::Communication &communication);
            /*static void end_game(NetworkManager &network_manager, rtype::ECSManager &ecs_manager,
                                 ntw::Communication &communication);*/

        private:
            asio::io_context m_io_context{};
            asio::ip::udp::resolver m_resolver;
            asio::ip::udp::endpoint m_receiver_endpoint;
            asio::ip::udp::socket m_socket;
            std::deque<ntw::Communication> m_queue{};
    };

    struct CommandHandler {
            ntw::NetworkType type;
            std::function<void(rclient::NetworkManager &, rtype::ECSManager &,
                               ntw::Communication &)>
                handler;
    };
} // namespace rclient