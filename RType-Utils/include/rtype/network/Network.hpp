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
        None,        // Nothing : None
        Start,       // Start the game : Start
        Connection,  // client trying to join a server's game : Connection
        Refusal,     // 1 client cannot join a server's game : Refusal
        Ok,          // Everything is good : Ok
        End,         // End the game for one player : End
        Creation,    // Create a new entity : Creation [Id] [Type]
        Destruction, // Destruct one entity : Destruction [Id]
        Position,    // Send the position of an entity : Position [Id] [x] [y]
        Input,       // Send the input of the player to server : Input [UP/RIGHT/DOWN/LEFT/W(Shooting)]
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
                    this->args[arg_ind++] = ' ';
                for (size_t i = arg_ind; i < MAX_SIZE && i < arg_ind + to_add.size(); i++) {
                    this->args[i] = to_add[ind];
                    ind++;
                }
            }

            std::vector<std::string> deserialize()
            {
                std::vector<std::string> dest{};
                size_t pos = 0;
                std::string src{this->args.data()};

                while ((pos = src.find_first_of(DELIMITORS.data())) != std::string::npos) {
                    dest.emplace_back(src.substr(0, pos));
                    pos = src.find_first_not_of(DELIMITORS.data(), pos);
                    src.erase(0, pos);
                }
                if (!src.empty())
                    dest.emplace_back(src);
                return dest;
            }
    };

#pragma pack(pop)
} // namespace ntw
