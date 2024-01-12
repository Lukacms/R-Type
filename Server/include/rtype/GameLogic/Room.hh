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
#include <rtype/ECSManager.hpp>
#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/PhysicsManager.hh>
#include <rtype/clients/Player.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <vector>

namespace rserver::game
{

    constexpr int MAX_ROOMS{100};
    constexpr int MAX_PLAYERS{4};

    // constexpr int TIMEOUT_WAITING{2 * 60};
    constexpr int TIMEOUT_WAITING{10};

    enum class RoomStatus { Lounge, Waiting, InGame };

    class Room
    {
        public:
            Room(asio::ip::udp::socket &psocket, std::size_t pid);
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
            [[nodiscard]] GameLogic &get_logic();
            void run_game_logic(rtype::utils::Clock &delta);
            void check_wait_timeout(float delta_time);
            [[nodiscard]] bool has_player(const Player &player);
            [[nodiscard]] rtype::ECSManager &get_ecs();

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
            std::shared_mutex ecs_mutex{};
            std::size_t id{0};
            dl::DlLoader<rtype::ECSManager> ecs{};
            dl::DlLoader<rtype::PhysicsManager> physics{};

            GameLogic logic{socket, ecs_mutex};
            std::vector<asio::ip::port_type> players{};
            PlayersManager manager{};
            RoomStatus status{RoomStatus::Waiting};
            rtype::utils::Clock timeout_connect{};
    };

} // namespace rserver::game
