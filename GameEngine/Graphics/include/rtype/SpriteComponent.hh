/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_component
*/

#pragma once

#include <SFML/Graphics.hpp>

struct SpriteComponent {
        sf::Sprite sprite;
        sf::Rect<int> texture_rect;
};
