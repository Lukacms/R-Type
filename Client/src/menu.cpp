/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** menu.cpp
*/

#include "menu.hh"

#include <SFML/Window/Mouse.hpp>
#include <chrono>
#include <iostream>
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
    sprite_system.loadTexture("START", "./Client/assets/menu_assets/START.png");
    sprite_system.loadTexture("music_button", "./Client/assets/menu_assets/MUTE.png");
    sprite_system.loadTexture("scale_button", "./Client/assets/menu_assets/UNMUTE.png");
    sprite_system.loadTexture("quit_button", "./Client/assets/menu_assets/QUIT.png");

    audio_system.loadSound("test", "./Client/assets/sounds/Spider-Dance.wav");
    audio_system.playSound("test");

    const Entity background{manager.create_entity()};
    const Entity start_button{manager.create_entity()};
    const Entity music_button{manager.create_entity()};
    const Entity scale_button{manager.create_entity()};
    const Entity quit_button{manager.create_entity()};

    sprites.emplace_at(background, sprite_system.createSprite("BGSprite", "BG"),
                       sf::Rect<int>{0, 0, 800, 600});
    sprites.emplace_at(start_button, sprite_system.createSprite("STARTSprite", "START"),
                       sf::Rect<int>{0, 0, 153, 48});
    sprites.emplace_at(music_button,
                       sprite_system.createSprite("music_buttonSprite", "music_button"),
                       sf::Rect<int>{0, 0, 153, 48});
    sprites.emplace_at(scale_button,
                       sprite_system.createSprite("scale_buttonSprite", "scale_button"),
                       sf::Rect<int>{0, 0, 153, 48});
    sprites.emplace_at(quit_button, sprite_system.createSprite("quit_buttonSprite", "quit_button"),
                       sf::Rect<int>{0, 0, 153, 48});

    transforms.emplace_at(background, 0.0F, 0.0F, 0.0F, 0.0F, 1.F, 1.F);
    transforms.emplace_at(start_button, 250.0F, 100.0F, 0.0F, 0.0F, 2.F, 2.F);
    transforms.emplace_at(music_button, 250.0F, 200.0F, 0.0F, 0.0F, 2.F, 2.F);
    transforms.emplace_at(scale_button, 250.0F, 300.0F, 0.0F, 0.0F, 2.F, 2.F);
    transforms.emplace_at(quit_button, 250.0F, 400.0F, 0.0F, 0.0F, 2.F, 2.F);

    manager.register_component(sprites);
    manager.register_component(tags);
    manager.register_component(transforms);
    std::function<void(ComponentManager &, float)> transform = &rtype::transform_system;
    std::function<void(ComponentManager &, float)> movement = &rtype::movement_system;
    std::function<void(ComponentManager &, float)> sprite = &rtype::sprite_system;
    manager.add_system(transform);
    manager.add_system(movement);
    manager.add_system(sprite);
    float delta_time = 0.F;

    while (le_client.is_running()) {
        le_client.render(manager);
        manager.apply_system(delta_time);
        le_client.read_input();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            const sf::Vector2i position = sf::Mouse::getPosition();
            if (position.x >= 300 && position.x <= 600 && position.y >= 225 && position.y <= 300)
                // TODO: Start game
                continue;
            if (position.x >= 300 && position.x <= 600 && position.y >= 325 && position.y <= 400)
                audio_system.setVolume("test", 0);
            if (position.x >= 300 && position.x <= 600 && position.y >= 425 && position.y <= 500)
                audio_system.setVolume("test", 100);
            if (position.x >= 300 && position.x <= 600 && position.y >= 525 && position.y <= 600)
                exit(0);
        }
    }
}
