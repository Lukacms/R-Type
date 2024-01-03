/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** utils
*/

#pragma once

#include <array>
#include <rtype/ECSManager.hpp>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace rserver
{

    bool is_number(std::string const &str);
    std::vector<std::string> split_delimitor(std::string &src, const std::string &del);
    std::vector<std::string> split_delimitor(std::string src, const std::string &del);
    void init_ecs(rtype::ECSManager &to_load);

    /**
     * @brief Get a number from a string
     *
     * @tparam TType - must be arithmetic
     * @param str - string to get nb from
     * @return TType
     */
    template <typename TType> TType get_number(const std::string &str)
    {
        if constexpr (!std::is_arithmetic_v<TType>)
            return TType{};
        TType dest{};
        std::stringstream strs{str};

        strs >> dest;
        return dest;
    }

} // namespace rserver
