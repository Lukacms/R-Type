/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** spriteManager
*/

#include <rtype/SpriteManager.hpp>

SpriteManager::SpriteManager()
{
}

bool SpriteManager::loadTexture(const std::string &name, const std::string &filename)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        return false;
    }

    textures[name] = texture;
    return true;
}

sf::Sprite SpriteManager::createSprite(const std::string &spriteName,
                                       const std::string &textureName)
{
    sf::Sprite sprite;

    if (textures.find(textureName) != textures.end()) {
        sprite.setTexture(textures[textureName]);
        sprites[spriteName] = sprite;
    };
    return sprite;
}

void SpriteManager::setPosition(const std::string &name, float x, float y)
{
    if (sprites.find(name) != sprites.end()) {
        sprites[name].setPosition(x, y);
    }
}

void SpriteManager::drawSprite(sf::RenderWindow &window, const std::string &name)
{
    if (sprites.find(name) != sprites.end()) {
        window.draw(sprites[name]);
    }
}
