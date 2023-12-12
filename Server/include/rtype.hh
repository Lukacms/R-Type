/*
** EPITECH PROJECT, 2023
** include
** File description:
** rtype
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <array>
#include <string_view>

#ifdef __unix__
    #define ENDL "\n"
#else
    #define ENDL "\r\n"
#endif

namespace rserver
{

    constexpr int SUCESS{0};
    constexpr int FAILURE{84};

    /* Log infos */
    constexpr std::string_view INFOS{"Info: "};
    constexpr std::string_view DEBUG{"Debug: "};
    constexpr std::string_view ERROR{"Error: "};

    constexpr std::string_view NUMBERS{"0123456789"};

    bool is_number(std::string const &str);
    std::size_t get_number(std::string const &str);

} // namespace rserver
