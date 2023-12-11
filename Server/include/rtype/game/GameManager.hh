/*
** EPITECH PROJECT, 2023
** game
** File description:
** GameManager
*/

#pragma once

namespace rserver
{

    class GameManager
    {
        public:
            GameManager() = default;
            GameManager(GameManager const &to_copy) = default;
            GameManager(GameManager &&to_move) = default;
            ~GameManager() = default;
            GameManager &operator=(GameManager const &to_copy) = default;
            GameManager &operator=(GameManager &&to_move) = default;

        private:
    };

} // namespace rserver
