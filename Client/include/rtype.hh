
/*
** EPITECH PROJECT, 2023
** include
** File description:
** rtype
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the client core
#define ASIO_HEADER_ONLY

#ifdef __unix__
    #define ENDL "\n"
#else
    #define ENDL "\r\n"
#endif

#ifdef NDEBUG
    #define DEBUG(x)
#else
    #define DEBUG(x) printf x
#endif

namespace rclient
{

    constexpr int SUCCESS{0};
    constexpr int FAILURE{84};

} // namespace rclient
