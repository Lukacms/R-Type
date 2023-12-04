/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Manager
*/

#pragma once

#include <asio.hpp>
#include <cstddef>

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
    };

} // namespace rserver
