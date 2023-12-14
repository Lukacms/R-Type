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

std::vector<std::string> rserver::split_delimitor(std::string &src, const std::string &del)
{
    std::vector<std::string> dest{};
    size_t pos = 0;

    while ((pos = src.find_first_of(del)) != std::string::npos) {
        dest.emplace_back(src.substr(0, pos));
        pos = src.find_first_not_of(del, pos);
        src.erase(0, pos);
    }
    if (!src.empty())
        dest.emplace_back(src);
    return dest;
}

std::vector<std::string> rserver::split_delimitor(std::string src, const std::string &del)
{
    std::vector<std::string> dest{};
    size_t pos = 0;

    while ((pos = src.find_first_of(del)) != std::string::npos) {
        dest.emplace_back(src.substr(0, pos));
        pos = src.find_first_not_of(del, pos);
        src.erase(0, pos);
    }
    if (!src.empty())
        dest.emplace_back(src);
    return dest;
}
