/*
** EPITECH PROJECT, 2023
** include
** File description:
** rtype
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#ifdef __unix__
    #define ENDL "\n"
#else
    #define ENDL "\r\n"
#endif

namespace rserver
{

    constexpr int SUCESS{0};
    constexpr int FAILURE{84};

} // namespace rserver
