/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_system
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <rtype/Registry.hpp>

class SpriteSystem
{
    public:
        void update(Registry &registry);
        void render(Registry &registry, std::unique_ptr<sf::RenderWindow> &renderer);
};
