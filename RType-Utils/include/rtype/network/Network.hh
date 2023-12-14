/*
** EPITECH PROJECT, 2023
** network
** File description:
** Network
*/

#pragma once

#include <array>
#include <string>
#include <string_view>

namespace ntw
{

    constexpr int MAX_SIZE{128};
    constexpr std::string_view DELIMITORS{" "};

    enum NetworkType {
        None,
        Start,
        End,         // Terminate the game of one client
        Connection,  // client trying to join a server's game
        Refusal,     // a client cannot join a server's game
        Ok,          // everything is good
        Creation,    // Creation of an Entity
        Destruction, // Destruction of an Entity
    };

#pragma pack(push, 1)

    struct Communication {
        public:
            NetworkType type{None};
            std::array<char, MAX_SIZE> args;
    };

#pragma pack(pop)
} // namespace ntw
