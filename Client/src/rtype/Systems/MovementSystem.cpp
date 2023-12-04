/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** movement_system
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <rtype/Components/TagComponent.hpp>
#include <rtype/Components/TransformComponent.hpp>
#include <rtype/Systems/MovementSystem.hpp>

void MovementSystem::update(Registry &registry)
{
    SparseArray<TransformComponent> &transforms = registry.get_components<TransformComponent>();
    SparseArray<TagComponent> &tags = registry.get_components<TagComponent>();

    for (size_t index = 0; index < transforms.size() && index < tags.size(); index += 1) {
        if (tags[index] == std::nullopt || transforms[index] == std::nullopt)
            continue;
        if (tags[index]->tag != "PLAYER")
            continue;
        transforms[index]->velocity_x = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? -1.0f :
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)                            ? 1.0f :
                                                                                         0.0f;
        transforms[index]->velocity_y = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? -1.0f :
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)                           ? 1.0f :
                                                                                       0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            transforms[index]->velocity_y = 0.F;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            transforms[index]->velocity_x = 0.F;
    }
}
