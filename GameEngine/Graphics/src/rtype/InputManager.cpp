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

void InputManager::update()
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

bool InputManager::is_key_pressed(sf::Keyboard::Key key) const
{
    auto it = keyMap.find(key);
    if (it != keyMap.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::is_mouse_button_pressed(sf::Mouse::Button button) const
{
    auto it = mouseButtonMap.find(button);
    if (it != mouseButtonMap.end()) {
        return it->second;
    }
    return false;
}

sf::Vector2i InputManager::get_mouse_position(const sf::Window &window) const
{
    return sf::Mouse::getPosition(window);
}
