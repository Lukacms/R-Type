/*
** EPITECH PROJECT, 2023
** clients
** File description:
** PlayersManager
*/

#pragma once

#include <cstddef>
#include <exception>
#include <rtype/clients/Player.hh>
#include <string_view>
#include <vector>

namespace rserver
{
    constexpr std::string_view NO_PLAYER{"No player found for this id."};
    constexpr std::string_view PM_ERROR{"PlayersManager error."};

    /**
     * @class PlayersManager
     * @brief Manage the players, to add / delete them
     *
     */
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
            [[nodiscard]] Player &get_by_id(asio::ip::port_type const &port);
            [[nodiscard]] Player &get_by_entity_id(std::size_t const &entity);
            [[nodiscard]] Player &get_by_entity_room_id(std::size_t const &entity,
                                                        const std::size_t &room);
            rserver::Player &add_player(asio::ip::udp::endpoint &endpoint);
            rserver::Player &add_player(Player &to_add);
            [[nodiscard]] std::size_t length() const;
            [[nodiscard]] std::vector<Player> get_all_players() const;
            void remove_player(Player &player);

            // void delete_player(asio::ip::udp::endpoint &endpoint);

            /* exception */
            class PlayersException : public std::exception
            {
                public:
                    PlayersException(std::string p_error = PM_ERROR.data());
                    PlayersException(PlayersException const &to_copy) = default;
                    PlayersException(PlayersException &&to_move) = default;
                    ~PlayersException() override = default;
                    PlayersException &operator=(PlayersException const &to_copy) = default;
                    PlayersException &operator=(PlayersException &&to_move) = default;
                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg{};
            };

        private:
            std::vector<Player> players{};
    };

} // namespace rserver
