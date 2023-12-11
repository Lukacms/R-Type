/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** textureManager
*/

#include <Manager/TextureManager.hpp>

TextureManager::TextureManager() {
}

bool TextureManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        return false;
    }

    textures[name] = std::move(texture);
    return true;
}

sf::Texture& TextureManager::getTexture(const std::string& name) {
    return textures.at(name);
}

void TextureManager::removeTexture(const std::string& name) {
    textures.erase(name);
}
