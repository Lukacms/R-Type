/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** menu.cpp
*/

#include "menu.hh"

#include <chrono>
#include <rtype/Client.hpp>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/WindowManager.hpp>

void rclient::Menu::menu()
{
    SparseArray<rtype::SpriteComponent> sprites{};
    SparseArray<rtype::TransformComponent> transforms{};
    SparseArray<rtype::TagComponent> tags{};
    SparseArray<rtype::BoxColliderComponent> colliders{};
    sprite_system.loadTexture("BG", "./Client/assets/backgrounds/024.png");
    sprite_system.loadTexture("button1", "./Client/assets/ui/PNG/Settings/text_0009_MUSIC.png");

    audio_system.loadSound("test", "./Client/assets/sounds/Spider-Dance.wav");
    audio_system.playSound("test");

    Entity background{manager.create_entity()};
    Entity button1{manager.create_entity()};
    sprites.emplace_at(background, sprite_system.createSprite("BGSprite", "BG"),
                       sf::Rect<int>{0, 0, 800, 600});
    sprites.emplace_at(button1, sprite_system.createSprite("button1Sprite", "button1"),
                       sf::Rect<int>{0, 0, 77, 14});
    transforms.emplace_at(background, 0.0F, 0.0F, 0.0F, 0.0F, 1.F, 1.F);
    transforms.emplace_at(button1, 500.0F, 1.0F, 0.0F, 0.0F, 2.F, 2.F);

    manager.register_component(sprites);
    manager.register_component(tags);
    manager.register_component(transforms);
    manager.register_component(colliders);
    std::function<void(ComponentManager &, float)> transform = &rtype::transform_system;
    std::function<void(ComponentManager &, float)> movement = &rtype::movement_system;
    std::function<void(ComponentManager &, float)> sprite = &rtype::sprite_system;
    std::function<void(ComponentManager &, float)> collider = &rtype::collider_system;
    manager.add_system(transform);
    manager.add_system(movement);
    manager.add_system(sprite);
    float delta_time = 0.F;
    while (le_client.is_running()) {
        auto start = std::chrono::high_resolution_clock::now();
        le_client.render(manager);
        manager.apply_system(delta_time);
        le_client.read_input();
        auto end = std::chrono::high_resolution_clock::now();
        delta_time =
            std::chrono::duration<float, std::chrono::seconds::period>(end - start).count();
    }
}
