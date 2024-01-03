/*
** EPITECH PROJECT, 2023
** src
** File description:
** utils
*/

#include <rtype.hh>
#include <sstream>
#include <string>

/**
 * @brief check if a string is composed only of numbers
 *
 * @param str-  string - to analyse
 * @return bool
 */
bool rserver::is_number(std::string const &str)
{
    return str.find_first_not_of(NUMBERS) == std::string::npos;
}

/**
 * @brief Split a string into a vector of string depending on the delimitors given
 *
 * @param src - string - to split
 * @param del - string - used to delimit parse
 * @return vector<string> that may be empty on error
 */
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

/**
 * @brief Split a string into a vector of string depending on the delimitors given
 *
 * @param src - string - to split; is given as copy instead of ref to construct it during the
 * prototype
 * @param del - string - used to delimit parse
 * @return vector<string> that may be empty on error
 */
std::vector<std::string> rserver::split_delimitor(std::string src, const std::string &del)
{
    std::vector<std::string> dest{};
    std::size_t pos = 0;

    while ((pos = src.find_first_of(del)) != std::string::npos) {
        dest.emplace_back(src.substr(0, pos));
        pos = src.find_first_not_of(del, pos);
        src.erase(0, pos);
    }
    if (!src.empty())
        dest.emplace_back(src);
    return dest;
}
