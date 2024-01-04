/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_component
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace rtype
{
    struct SpriteComponent {
            sf::Sprite sprite{};
            std::string texture_path{};
    };
} // namespace rtype
