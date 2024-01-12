/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** RoomsManager
*/

#pragma once

#include <cstddef>
#include <rtype/GameLogic/Room.hh>
#include <vector>

namespace rserver::game
{

    class RoomsManager
    {
        public:
            RoomsManager(PlayersManager &pmanager);
            RoomsManager(RoomsManager const &to_copy) = delete;
            RoomsManager(RoomsManager &&to_move);
            ~RoomsManager() = default;
            RoomsManager &operator=(RoomsManager const &to_copy) = delete;
            RoomsManager &operator=(RoomsManager &&to_move) = delete;

            /* methods */
            void join_random_room(Player &player);
            void join_room(Player &player, const std::size_t &room_id);
            void add_room(Player &first_player, const std::size_t &nb_threads,
                          asio::ip::udp::socket &socket);
            void leave_room_with_id(Player &player, const std::size_t &room_id);
            [[nodiscard]] Room &get_room_by_id(const std::size_t &room_id);
            [[nodiscard]] std::vector<Room> &get_rooms();

        private:
            std::vector<rserver::game::Room> rooms{};
            std::size_t last_id{0};

            PlayersManager &manager;
    };

} // namespace rserver::game
