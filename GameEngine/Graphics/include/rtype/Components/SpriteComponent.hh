/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_component
*/

#pragma once

#include <rtype/utils/Vector2D.hh>
#include <string>

namespace rtype
{
    struct SpriteComponent {
            rtype::utils::TextureRect rectangle{};
            std::string texture_path{};
            rtype::utils::Vector2D<float> origin{};
    };
} // namespace rtype
