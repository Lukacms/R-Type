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
        Start,
        None,
    };

#pragma pack(push, 1)

    struct Communication {
        public:
            NetworkType type{None};
            std::array<char, MAX_SIZE> args;
    };

#pragma pack(pop)
} // namespace ntw
