/*
** EPITECH PROJECT, 2023
** clients
** File description:
** Player
*/

#pragma once

#include <asio.hpp>
#include <string_view>

namespace rserver
{

    constexpr std::string_view NEW_CLIENT{"New client with ip "};
    constexpr std::string_view MOVE_CLIENT{"Moved client to new instance, with ip "};
    constexpr std::string_view DEL_CLIENT{"Client will be deleted, with ip "};

    class Player
    {
        public:
            /* constructor / destructor */
            Player(asio::ip::port_type p_port);
            Player(Player const &to_copy) = delete;
            Player(Player &&to_move);
            ~Player();

            /* operator overload */
            Player &operator=(Player const &to_copy) = delete;
            Player &operator=(Player &&to_move);
            [[nodiscard]] bool operator==(asio::ip::port_type &p_port) const;

        private:
            asio::ip::port_type port;
    };

} // namespace rserver
