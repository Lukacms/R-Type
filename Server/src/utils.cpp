/*
** EPITECH PROJECT, 2023
** src
** File description:
** utils
*/

#include <rtype.hh>
#include <sstream>
#include <string>

bool rserver::is_number(std::string const &str)
{
    return str.find_first_not_of(NUMBERS) == std::string::npos;
}

std::size_t rserver::get_number(std::string const &str)
{
    std::size_t dest = 0;
    std::stringstream strs{str};

    strs >> dest;
    return dest;
}
