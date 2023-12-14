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

        void update(const sf::Window &window);
        bool isKeyPressed(sf::Keyboard::Key key) const;
        bool isMouseButtonPressed(sf::Mouse::Button button) const;
        sf::Vector2i getMousePosition(const sf::Window &window) const;

    private:
        std::unordered_map<sf::Keyboard::Key, bool> keyMap;
        std::unordered_map<sf::Mouse::Button, bool> mouseButtonMap;
};
