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
            sf::Sprite sprite{};
            sf::Texture texture{};
    };
} // namespace rtype
