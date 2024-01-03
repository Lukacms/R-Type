/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_component
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <rtype/Components/AnimationComponent.hh>

namespace rtype
{
    struct SpriteComponent {
            sf::Sprite sprite{};
            TextureRect rectangle{};
            std::string texture_path{};
    };
} // namespace rtype
