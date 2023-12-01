/*
** EPITECH PROJECT, 2023
** network
** File description:
** Network
*/

#pragma once

#include <string>
#include <vector>

namespace ntw
{
    enum NetworkType {
        Start,
        None,
    };

    struct Communication {
        public:
            NetworkType type{None};
            std::string args{};
    };
} // namespace ntw
