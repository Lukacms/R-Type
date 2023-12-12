/*
** EPITECH PROJECT, 2023
** clients
** File description:
** PlayersManager
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <exception>
#include <rtype/clients/Player.hh>
#include <string_view>
#include <vector>

namespace rserver
{
    constexpr std::string_view NO_PLAYER{"No player found for this id."};
    constexpr std::string_view PM_ERROR{"PlayersManager error."};

    class PlayersManager
    {
        public:
            PlayersManager() = default;
            PlayersManager(PlayersManager const &to_copy) = default;
            PlayersManager(PlayersManager &&to_move) = default;
            ~PlayersManager() = default;
            PlayersManager &operator=(PlayersManager const &to_copy) = default;
            PlayersManager &operator=(PlayersManager &&to_move) = default;

            /* methods */
            Player &get_by_id(asio::ip::port_type const &port);
            void add_player(asio::ip::udp::endpoint &endpoint, asio::ip::udp::socket &socket);

            /* exception */
            class PlayersExceptions : public std::exception
            {
                public:
                    PlayersExceptions(std::string p_error = PM_ERROR.data());
                    PlayersExceptions(PlayersExceptions const &to_copy) = default;
                    PlayersExceptions(PlayersExceptions &&to_move) = default;
                    ~PlayersExceptions() override = default;
                    PlayersExceptions &operator=(PlayersExceptions const &to_copy) = default;
                    PlayersExceptions &operator=(PlayersExceptions &&to_move) = default;
                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg{};
            };

        private:
            std::vector<Player> players{};
    };

} // namespace rserver
