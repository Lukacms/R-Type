/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** menu.cpp
*/

#include "menu.hh"

#include <SFML/Window/Mouse.hpp>
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
    sprite_system.loadTexture("START", "./Client/assets/menu_assets/START.png");
    sprite_system.loadTexture("mute_button", "./Client/assets/menu_assets/MUTE.png");
    sprite_system.loadTexture("unmute_button", "./Client/assets/menu_assets/UNMUTE.png");
    sprite_system.loadTexture("quit_button", "./Client/assets/menu_assets/QUIT.png");

    audio_system.loadSound("music", "./Client/assets/sounds/Spider-Dance.wav");
    audio_system.playSound("music");

    const Entity background{manager.create_entity()};
    const Entity start_button{manager.create_entity()};
    const Entity mute_button{manager.create_entity()};
    const Entity unmute_button{manager.create_entity()};
    const Entity quit_button{manager.create_entity()};

    const sf::Vector2u initial_window_size = le_client.get_window_size();

    sprites.emplace_at(background, sprite_system.createSprite("BGSprite", "BG"),
                       sf::Rect<int>{0, 0, static_cast<int>(initial_window_size.x),
                                     static_cast<int>(initial_window_size.y)});

    sprites.emplace_at(start_button, sprite_system.createSprite("STARTSprite", "START"),
                       sf::Rect<int>{0, 0, static_cast<int>(initial_window_size.x / 4.0),
                                     static_cast<int>(initial_window_size.y / 4.0)});

    sprites.emplace_at(mute_button, sprite_system.createSprite("mute_buttonSprite", "mute_button"),
                       sf::Rect<int>{0, 0, static_cast<int>(initial_window_size.x / 4.0),
                                     static_cast<int>(initial_window_size.y / 4.0 + 100)});
    sprites.emplace_at(unmute_button,
                       sprite_system.createSprite("unmute_buttonSprite", "unmute_button"),
                       sf::Rect<int>{0, 0, static_cast<int>(initial_window_size.x / 4.0),
                                     static_cast<int>(initial_window_size.y / 4.0 + 200)});
    sprites.emplace_at(quit_button, sprite_system.createSprite("quit_buttonSprite", "quit_button"),
                       sf::Rect<int>{0, 0, static_cast<int>(initial_window_size.x / 4.0),
                                     static_cast<int>(initial_window_size.y / 4.0 + 300)});

    transforms.emplace_at(background, 0.0F, 0.0F, 0.0F, 0.0F, 1.F, 1.F);
    transforms.emplace_at(start_button, initial_window_size.x / 4.0, initial_window_size.y / 4.0,
                          0.0F, 0.0F, 2.0F, 2.0F);
    transforms.emplace_at(mute_button, initial_window_size.x / 4.0,
                          initial_window_size.y / 4.0 + 100, 0.0F, 0.0F, 2.0F, 2.0F);
    transforms.emplace_at(unmute_button, initial_window_size.x / 4.0,
                          initial_window_size.y / 4.0 + 200, 0.0F, 0.0F, 2.0F, 2.0F);
    transforms.emplace_at(quit_button, initial_window_size.x / 4.0,
                          initial_window_size.y / 4.0 + 300, 0.0F, 0.0F, 2.0F, 2.0F);

    tags.emplace_at(background, "background");
    tags.emplace_at(start_button, "start_button");
    tags.emplace_at(mute_button, "mute_button");
    tags.emplace_at(unmute_button, "unmute_button");
    tags.emplace_at(quit_button, "quit_button");

    manager.register_component(sprites);
    manager.register_component(tags);
    manager.register_component(transforms);
    std::function<void(ComponentManager &, float)> transform = &rtype::transform_system;
    std::function<void(ComponentManager &, float)> movement = &rtype::movement_system;
    std::function<void(ComponentManager &, float)> sprite = &rtype::sprite_system;
    manager.add_system(transform);
    manager.add_system(movement);
    manager.add_system(sprite);

    while (le_client.is_running()) {
        constexpr float delta_time = 0.F;
        le_client.render(manager);
        manager.apply_system(delta_time);
        le_client.read_input();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            const auto window_size = le_client.get_window_size();
            const auto mouse_position = sf::Mouse::getPosition(le_client.get_window());
            if (mouse_position.x >= window_size.x / 4.0 &&
                mouse_position.x <= window_size.x / 4.0 + 306.0 &&
                mouse_position.y >= window_size.y / 4.0 &&
                mouse_position.y <= window_size.y / 4.0 + 96.0) {
                continue;
                // TODO: Start game
            }
            if (mouse_position.x >= window_size.x / 4.0 &&
                mouse_position.x <= window_size.x / 4.0 + 306.0 &&
                mouse_position.y >= window_size.y / 4.0 + 100 &&
                mouse_position.y <= window_size.y / 4.0 + 196.0) {
                audio_system.setVolume("music", 0);
            }
            if (mouse_position.x >= window_size.x / 4.0 &&
                mouse_position.x <= window_size.x / 4.0 + 306.0 &&
                mouse_position.y >= window_size.y / 4.0 + 200 &&
                mouse_position.y <= window_size.y / 4.0 + 296.0) {
                audio_system.setVolume("music", 100);
            }
            if (mouse_position.x >= window_size.x / 4.0 &&
                mouse_position.x <= window_size.x / 4.0 + 306.0 &&
                mouse_position.y >= window_size.y / 4.0 + 300 &&
                mouse_position.y <= window_size.y / 4.0 + 396.0) {
                le_client.close_window();
            }
        }
    }
}
