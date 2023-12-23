/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#include <rtype/InputManager.hpp>

InputManager::InputManager() = default;

void InputManager::update()
{
    for (int key = sf::Keyboard::Key::A; key != sf::Keyboard::KeyCount; ++key) {
        keyMap[static_cast<sf::Keyboard::Key>(key)] =
            sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
    }

    for (int button{static_cast<int>(sf::Mouse::Button::Left)}; button != sf::Mouse::ButtonCount;
         ++button) {
        mouseButtonMap[static_cast<sf::Mouse::Button>(button)] =
            sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }
}

bool InputManager::is_key_pressed(sf::Keyboard::Key key) const
{
    auto input = keyMap.find(key);

    if (input != keyMap.end()) {
        return input->second;
    }
    return false;
}

bool InputManager::is_mouse_button_pressed(sf::Mouse::Button button) const
{
    auto input = mouseButtonMap.find(button);

    if (input != mouseButtonMap.end()) {
        return input->second;
    }
    return false;
}

sf::Vector2i InputManager::get_mouse_position(const sf::Window &window) const // NOLINT
{
    return sf::Mouse::getPosition(window);
}
