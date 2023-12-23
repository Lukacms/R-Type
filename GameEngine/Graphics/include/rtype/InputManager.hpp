/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>

class InputManager
{
    public:
        InputManager();

        void update();
        bool is_key_pressed(sf::Keyboard::Key key) const;
        bool is_mouse_button_pressed(sf::Mouse::Button button) const;
        sf::Vector2i get_mouse_position(const sf::Window &window) const;

    private:
        std::unordered_map<sf::Keyboard::Key, bool> keyMap{};
        std::unordered_map<sf::Mouse::Button, bool> mouseButtonMap{};
};
