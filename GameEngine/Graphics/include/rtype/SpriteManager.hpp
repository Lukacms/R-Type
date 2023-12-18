/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** spriteManager
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class SpriteManager
{
    public:
        SpriteManager();

        bool loadTexture(const std::string &name, const std::string &filename);
        sf::Sprite createSprite(const std::string &spriteName, const std::string &textureName);
        void setPosition(const std::string &name, float x, float y);
        void drawSprite(sf::RenderWindow &window, const std::string &name);

    private:
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::Sprite> sprites;
};