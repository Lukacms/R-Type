/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** Room
*/

#pragma once

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/clients/Player.hh>
#include <vector>

namespace rserver::game
{

    constexpr int MAX_ROOMS{100};
    constexpr int MAX_PLAYERS{4};

    enum RoomStatus { Waiting, InGame };

    class Room
    {
        public:
            Room(std::shared_mutex &pecs, asio::ip::udp::socket &psocket, PlayersManager &pmanager,
                 std::size_t pid);
            Room(Room const &to_copy) = delete;
            Room(Room &&to_move);
            ~Room();
            Room &operator=(Room const &to_copy) = delete;
            Room &operator=(Room &&to_move) = delete;

            /* methods */
            void add_player(Player &new_player);
            [[nodiscard]] const RoomStatus &get_status() const;
            [[nodiscard]] std::size_t get_nb_players() const;
            [[nodiscard]] std::size_t get_id() const;
            void del_player(Player &to_del);

            class RoomException : public std::exception
            {
                public:
                    RoomException(std::string &&perror = "Error");
                    RoomException(RoomException const &to_copy) = default;
                    RoomException(RoomException &&to_move) = default;
                    ~RoomException() override = default;
                    RoomException &operator=(RoomException const &to_copy) = default;
                    RoomException &operator=(RoomException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg;
            };

        private:
            asio::ip::udp::socket &socket;
            std::shared_mutex &ecs_mutex;

            std::size_t id{0};
            GameLogic logic{socket, ecs_mutex};
            std::vector<asio::ip::port_type> players{};
            PlayersManager &manager;
            RoomStatus status{Waiting};
    };

} // namespace rserver::game
