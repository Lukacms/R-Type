/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Manager
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#include <string_view>
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <exception>
#include <rtype/clients/MessageQueue.hh>
#include <rtype/clients/Player.hh>
#include <rtype/clients/PlayersManager.hh>
#include <vector>

namespace rserver
{

    constexpr size_t DEFAULT_PORT{8080};
    constexpr std::string_view DEFAULT_ERROR{"Error"};

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
            [[noreturn]] void do_loop();
            void handle_command();
            void command_manager(Player &player, Message const &message);

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
            asio::io_context context{};
            asio::ip::udp::socket socket;
            asio::error_code ignored{};

            PlayersManager players{};
            MessageQueue queue{};
    };

} // namespace rserver
