/*
** EPITECH PROJECT, 2023
** Components
** File description:
** TextComponent
*/

#pragma once

#include <rtype/utils/Color.hh>
#include <rtype/utils/Vector2D.hpp>
#include <string>

namespace rtype
{
    struct TextComponent {
            rtype::utils::Colors colors{};
            unsigned int opacity{};
            unsigned int font_size{};
            std::string text{};
            std::string font_path{};
            rtype::utils::Vector2D<float> origin{};
    };

} // namespace rtype
