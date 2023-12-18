/*
** EPITECH PROJECT, 2023
** network
** File description:
** Network
*/

#pragma once

#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

namespace ntw
{

    constexpr int MAX_SIZE{128};
    constexpr std::string_view DELIMITORS{" "};

    enum NetworkType {
        None,
        Start,
        Connection,  // client trying to join a server's game
        Refusal,     // a client cannot join a server's game
        Ok,          // everything is good
        End,         // End the game for one player
        Creation,    // Create a new entity
        Destruction, // Destruct one entity
        Input,       // Input recieved from client to move
    };

#pragma pack(push, 1)

    struct Communication {
        public:
            /* variables */
            NetworkType type{None};
            std::array<char, MAX_SIZE> args;

            /* methods */
            template <typename TType> void add_param(TType param)
            {
                std::string to_add{};
                size_t ind{0};
                size_t arg_ind{0};

                if constexpr (std::is_arithmetic<TType>::value)
                    to_add = std::to_string(param);
                else
                    to_add = param;
                while (this->args[arg_ind]) {
                    arg_ind++;
                }
                if (arg_ind != 0)
                    this->args[arg_ind++] = DELIMITORS[0];
                for (size_t i = arg_ind; i < MAX_SIZE && i < arg_ind + to_add.size(); i++) {
                    this->args[i] = to_add[ind];
                    ind++;
                }
            }
    };

#pragma pack(pop)
} // namespace ntw
