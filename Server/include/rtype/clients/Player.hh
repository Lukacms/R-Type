/*
** EPITECH PROJECT, 2023
** clients
** File description:
** Player
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <shared_mutex>
#include <string_view>

namespace rserver
{

    constexpr std::string_view NEW_CLIENT{"New client with ip "};
    constexpr std::string_view MOVE_CLIENT{"Moved client to new instance, with ip "};
    constexpr std::string_view DEL_CLIENT{"Client will be deleted, with ip "};

    enum class PlayerStatus { Lobby, Room, Game };

    struct Vector2f {
        public:
            float pos_x{0.0};
            float pos_y{0.0};
    };

    constexpr float POSITION_CHANGE{1.0};
    constexpr float OFFSET_Y_BULLET{11};
    constexpr float PLAYER_SPEED{1000};

    class Player
    {
        public:
            std::shared_mutex mutex{};
            /* constructor / destructor */
            Player(asio::ip::udp::endpoint p_endpoint);
            Player(Player const &to_copy) = delete;
            Player(Player &&to_move);
            ~Player();

            /* operator overload */
            Player &operator=(Player const &to_copy) = delete;
            Player &operator=(Player &&to_move);
            [[nodiscard]] bool operator==(asio::ip::port_type &port) const;

            /* methods */
            [[nodiscard]] asio::ip::port_type get_port() const;
            [[nodiscard]] asio::ip::udp::endpoint get_endpoint() const;
            [[nodiscard]] const std::size_t &get_entity_value() const;
            [[nodiscard]] const PlayerStatus &get_status() const;
            void set_status(const PlayerStatus &new_status);
            void set_entity_value(std::size_t const &value);
            void level_up();
            std::size_t get_level();
            void lock();
            void unlock();

        private:
            asio::ip::udp::endpoint endpoint;
            std::size_t entity_value{};
            // PlayerStatus status{PlayerStatus::Lobby};
            std::size_t level{1};
            PlayerStatus status{PlayerStatus::Game};
    };

} // namespace rserver
