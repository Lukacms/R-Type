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
#include <rtype/clients/MessageQueue.hh>
#include <rtype/clients/Player.hh>
#include <vector>

namespace rserver
{

    constexpr size_t DEFAULT_PORT{8080};

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

        private:
            asio::io_context context{};
            asio::ip::udp::socket socket;

            std::vector<Player> players{};
            MessageQueue queue{};
    };

} // namespace rserver
