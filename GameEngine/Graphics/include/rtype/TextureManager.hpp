/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** textureManager
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager
{
    public:
        TextureManager();

        bool loadTexture(const std::string &name, const std::string &filename);
        sf::Texture &getTexture(const std::string &name);
        void removeTexture(const std::string &name);

    private:
        std::unordered_map<std::string, sf::Texture> textures;
};
