/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Manager
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <exception>
#include <rtype/ECSManager.hpp>
#include <rtype/GameLogic/RoomsManager.hh>
#include <rtype/SparseArray.hpp>
#include <rtype/clients/Player.hh>
#include <rtype/clients/PlayersManager.hh>
#include <rtype/clients/ThreadPool.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/network/Network.hpp>
#include <shared_mutex>
#include <string_view>
#include <vector>

namespace rserver
{

    constexpr size_t DEFAULT_PORT{8080};
    constexpr short int TIMEOUT_MS{200};
    constexpr float TIMEOUT_GL{1000000.0};
    constexpr std::string_view ECS_SL_PATH{"./libs/r-type-ecs.so"};
    constexpr std::string_view PHYSICS_SL_PATH{"./libs/r-type-physics.so"};

    /* exceptions */
    constexpr std::string_view DEFAULT_ERROR{"Error"};
    constexpr std::string_view WRONG_ARGUMENTS{"Error while analyzing the arguments."};

    /**
     * @class Manager
     * @brief manager class for the server.
     * Will handle retrieving commmands, parsing them and doing the necessary actions
     *
     */
    class Manager
    {
        public:
            /* constructors / destructors */
            Manager(asio::ip::port_type port = DEFAULT_PORT);
            Manager(Manager const &to_copy) = delete;
            Manager(Manager &&to_move);
            ~Manager();
            /* operator overload */
            Manager &operator=(Manager const &to_copy) = delete;
            Manager &operator=(Manager &&to_move);

            /* methods */
            static void launch(asio::ip::port_type port = DEFAULT_PORT);
            static void send_message(const ntw::Communication &to_send, const Player &client,
                                     asio::ip::udp::socket &udp_socket);
            /**
             * @brief Send a message to all player that have the same status at the one given in
             * param
             *
             * @param to_send Communication - message
             * @param players PlayersManager - all players
             * @param udp_socket udp::socket - socket to send from
             * @param status PlayerStatus - status required for the player to have
             */
            static void send_message(const ntw::Communication &to_send,
                                     const PlayersManager &players,
                                     asio::ip::udp::socket &udp_socket, const PlayerStatus &status);
            static void send_to_all(ntw::Communication &to_send, PlayersManager &players,
                                    asio::ip::udp::socket &udp_socket);

            /* udp methods */
            void start_receive();

            /* function pointers for commands */
            /* They have to be public to be called */
            void input_handler(Player &, std::vector<std::string> &);
            void end_handler(Player &, std::vector<std::string> &);
            void room_handler(Player &, std::vector<std::string> &);

            /* exception */
            class ManagerException : public std::exception
            {
                public:
                    ManagerException(std::string p_error = DEFAULT_ERROR.data());
                    ManagerException(ManagerException const &to_copy) = default;
                    ManagerException(ManagerException &&to_move) = default;
                    ~ManagerException() override = default;
                    ManagerException &operator=(ManagerException const &to_copy) = default;
                    ManagerException &operator=(ManagerException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error{};
            };

        private:
            /* variables */
            asio::io_context context{};
            asio::error_code ignored{};

            /* udp, will handle the majority of the events */
            asio::ip::udp::socket udp_socket;
            asio::ip::udp::endpoint endpoint{};

            /* main variables */
            PlayersManager players{};
            ThreadPool threads{};
            game::RoomsManager rooms{this->players};
            game::GameLogic logic;
            dl::DlLoader<rtype::ECSManager> ecs{};
            dl::DlLoader<rtype::PhysicsManager> physics{};

            /* utils */
            std::shared_mutex ecs_mutex{};
            std::shared_mutex rooms_mutex{};

            /* methods */
            static void handle_disconnection(int);
            void command_manager(ntw::Communication const &communication,
                                 asio::ip::udp::endpoint &client);
            void refuse_client(asio::ip::udp::endpoint &client);
            void add_new_player(asio::ip::udp::endpoint &client);
            void lobby_handler();
            void shoot_according_level(Player &);
            void run_game_logic();
            void run_all_rooms_logics(rtype::utils::Clock &delta);
    };

    struct CommandHandler {
            ntw::NetworkType type;
            std::function<void(Manager &, Player &, std::vector<std::string> &)> handler;
    };

} // namespace rserver
