/*
** EPITECH PROJECT, 2023
** utils
** File description:
** Clock
*/

#pragma once

#include <chrono>

namespace rtype::utils
{

    /**
     * @class Clock
     * @brief Class to keep track of time. Can be reset, and can get time in seconds or miliseconds
     *
     */
    class Clock
    {
        public:
            Clock() = default;
            Clock(Clock const &to_copy) = default;
            Clock(Clock &&to_move) = default;
            ~Clock() = default;
            Clock &operator=(Clock const &to_copy) = default;
            Clock &operator=(Clock &&to_move) = default;

            /* methods */
            [[nodiscard]] std::chrono::duration<double> get_elapsed_time();
            [[nodiscard]] double get_elapsed_time_in_s();
            [[nodiscard]] double get_elapsed_time_in_ms();
            void reset();

        private:
            std::chrono::time_point<std::chrono::steady_clock> start{
                std::chrono::steady_clock::now()};
            std::chrono::time_point<std::chrono::steady_clock> updated{
                std::chrono::steady_clock::now()};
    };

} // namespace rtype::utils
