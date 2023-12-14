/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#include <rtype/InputManager.hpp>

InputManager::InputManager()
{
}

void InputManager::update(const sf::Window &window)
{
    for (int key = sf::Keyboard::Key::A; key != sf::Keyboard::Key::KeyCount; ++key) {
        keyMap[static_cast<sf::Keyboard::Key>(key)] =
            sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
    }

    for (int button = sf::Mouse::Button::Left; button != sf::Mouse::Button::ButtonCount; ++button) {
        mouseButtonMap[static_cast<sf::Mouse::Button>(button)] =
            sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key) const
{
    auto it = keyMap.find(key);
    if (it != keyMap.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::isMouseButtonPressed(sf::Mouse::Button button) const
{
    auto it = mouseButtonMap.find(button);
    if (it != mouseButtonMap.end()) {
        return it->second;
    }
    return false;
}

sf::Vector2i InputManager::getMousePosition(const sf::Window &window) const
{
    return sf::Mouse::getPosition(window);
}
