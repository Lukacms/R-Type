/*
** EPITECH PROJECT, 2023
** utils
** File description:
** Clock
*/

#include <rtype/utils/Clock.hh>

std::chrono::duration<double> rtype::utils::Clock::get_elapsed_time()
{
    this->updated = std::chrono::steady_clock::now();

    return updated - start;
}

double rtype::utils::Clock::get_elapsed_time_in_s()
{
    auto tmp{this->get_elapsed_time()};

    return tmp.count();
}

double rtype::utils::Clock::get_elapsed_time_in_ms()
{
    this->updated = std::chrono::steady_clock::now();
    auto tmp{std::chrono::duration_cast<std::chrono::milliseconds>(this->updated - this->start)};

    return tmp.count();
}

/**
 * reset the clock
 */
void rtype::utils::Clock::reset()
{
    this->start = std::chrono::steady_clock::now();
    this->updated = std::chrono::steady_clock::now();
}
