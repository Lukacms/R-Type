/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** menu.hh
*/

#pragma once

#include <rtype/AudioManager.hpp>
#include <rtype/Client.hpp>
#include <rtype/ECSManager.hpp>
#include <rtype/SpriteManager.hpp>
#include <rtype/TextureManager.hpp>
#include <rtype/WindowManager.hpp>

namespace rclient
{
    class Menu
    {
        public:
            Menu() = default;
            ~Menu() = default;
            void menu();

        private:
            AudioManager audio_system{};
            TextureManager texture_system{};
            SpriteManager sprite_system{};
            rclient::Client le_client{};
            rtype::ECSManager manager{};
            WindowManager window_manager{};
    };
} // namespace rclient
