/*
** EPITECH PROJECT, 2023
** config
** File description:
** ArgsConfig
*/

#pragma once

namespace rclient
{

    class ArgsConfig
    {
        public:
            ArgsConfig() = default;
            ArgsConfig(ArgsConfig const &to_copy) = default;
            ArgsConfig(ArgsConfig &&to_move) = default;
            ~ArgsConfig() = default;
            ArgsConfig &operator=(ArgsConfig const &to_copy) = default;
            ArgsConfig &operator=(ArgsConfig &&to_move) = default;

        private:
    };

} // namespace rclient
