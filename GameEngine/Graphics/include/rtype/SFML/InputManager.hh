/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>

namespace rtype
{
    class InputManager
    {
        public:
            InputManager();

            void update();
            [[nodiscard]] bool is_key_pressed(sf::Keyboard::Key key) const;
            [[nodiscard]] bool is_mouse_button_pressed(sf::Mouse::Button button) const;
            [[nodiscard]] sf::Vector2i get_mouse_position(const sf::Window &window) const;

        private:
            std::unordered_map<sf::Keyboard::Key, bool> key_map{};
            std::unordered_map<sf::Mouse::Button, bool> mouse_button_map{};
    };
} // namespace rtype
