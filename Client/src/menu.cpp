/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** menu.cpp
*/

#include <rtype/AudioManager.hpp>
#include <rtype/SpriteManager.hpp>
#include <rtype/TextureManager.hpp>

void menu()
{
    AudioManager audio_system{};
    TextureManager texture_system{};
    SpriteManager sprite_system{};

    sprite_system.createSprite("background", "./Client/assets/backgrounds/024.png");
    sprite_system.loadTexture("background", "./Client/assets/backgrounds/024.png");
}
