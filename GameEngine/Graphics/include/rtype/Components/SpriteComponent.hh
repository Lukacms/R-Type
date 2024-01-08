/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_component
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <rtype/utils/Vector2D.hpp>

namespace rtype
{
    struct SpriteComponent {
            rtype::utils::TextureRect rectangle{};
            std::string texture_path{};
            rtype::utils::Vector2D<float> origin{};
    };
} // namespace rtype
