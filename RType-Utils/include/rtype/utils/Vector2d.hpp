/*
** EPITECH PROJECT, 2023
** utils
** File description:
** Vector2d
*/

#pragma once

namespace rtype::utils
{

    template <typename TType> struct Vector2d {
        public:
            /* variables */
            TType x{0};
            TType y{0};
    };

} // namespace rtype::utils
