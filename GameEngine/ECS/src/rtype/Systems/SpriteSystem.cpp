/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_system
*/

#include <iostream>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Systems/SpriteSystem.hh>

void SpriteSystem::update(Registry &registry)
{
    SparseArray<SpriteComponent> &sprites = registry.get_components<SpriteComponent>();
    SparseArray<TransformComponent> &transforms = registry.get_components<TransformComponent>();

    for (size_t index = 0; index < sprites.size() && index < sprites.size(); index += 1) {
        if (sprites[index] == std::nullopt || transforms[index] == std::nullopt)
            continue;
        sprites[index]->sprite.setPosition(transforms[index]->position_x,
                                           transforms[index]->position_y);
        sprites[index]->sprite.setScale(transforms[index]->scale_x, transforms[index]->scale_x);
        sprites[index]->sprite.setTextureRect(sprites[index]->texture_rect);
    }
}

void SpriteSystem::render(Registry &registry, std::unique_ptr<sf::RenderWindow> &renderer)
{
    SparseArray<SpriteComponent> sprites = registry.get_components<SpriteComponent>();

    for (auto &sprite : sprites) {
        if (!sprite.has_value())
            continue;
        renderer->draw(sprite.value().sprite);
    }
}
