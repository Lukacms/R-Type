/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_component
*/

#include <SFML/Graphics.hpp>

namespace rtype
{
    struct SpriteComponent {
            sf::Sprite sprite;
            sf::Rect<int> texture_rect;
    };
} // namespace rtype
