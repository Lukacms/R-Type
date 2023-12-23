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
#include <mutex>
#include <string_view>

namespace rserver
{

    constexpr std::string_view NEW_CLIENT{"New client with ip "};
    constexpr std::string_view MOVE_CLIENT{"Moved client to new instance, with ip "};
    constexpr std::string_view DEL_CLIENT{"Client will be deleted, with ip "};

    struct Vector2f {
        public:
            float pos_x{0.0};
            float pos_y{0.0};
    };

    constexpr float POSITION_CHANGE{1.0};
    constexpr float PLAYER_SPEED{1000};

    class Player
    {
        public:
            std::mutex mutex{};
            /* constructor / destructor */
            Player(asio::ip::udp::endpoint p_endpoint);
            Player(Player const &to_copy) = delete;
            Player(Player &&to_move);
            ~Player() = default;

            /* operator overload */
            Player &operator=(Player const &to_copy) = delete;
            Player &operator=(Player &&to_move);
            [[nodiscard]] bool operator==(asio::ip::port_type &port) const;

            /* methods */
            [[nodiscard]] asio::ip::port_type get_port() const;
            [[nodiscard]] asio::ip::udp::endpoint get_endpoint() const;
            [[nodiscard]] std::size_t get_entity_value() const;
            void set_entity_value(std::size_t const &value);
            void lock();
            void unlock();

        private:
            asio::ip::udp::endpoint endpoint;
            std::size_t entity_value{};
    };

} // namespace rserver
