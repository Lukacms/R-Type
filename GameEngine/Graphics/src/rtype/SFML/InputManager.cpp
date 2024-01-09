/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#include <rtype/SFML/InputManager.hh>

rtype::InputManager::InputManager() = default;

void rtype::InputManager::update()
{
    for (int key = sf::Keyboard::Key::A; key != sf::Keyboard::KeyCount; ++key) {
        key_map[static_cast<sf::Keyboard::Key>(key)] =
            sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
    }

    for (int button{static_cast<int>(sf::Mouse::Button::Left)}; button != sf::Mouse::ButtonCount;
         ++button) {
        mouse_button_map[static_cast<sf::Mouse::Button>(button)] =
            sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }
}

bool rtype::InputManager::is_key_pressed(sf::Keyboard::Key key) const
{
    auto input{key_map.find(key)};

    if (input != key_map.end()) {
        return input->second;
    }
    return false;
}

bool rtype::InputManager::is_mouse_button_pressed(sf::Mouse::Button button) const
{
    auto input{mouse_button_map.find(button)};

    if (input != mouse_button_map.end()) {
        return input->second;
    }
    return false;
}

sf::Vector2i rtype::InputManager::get_mouse_position(const sf::Window &window) const // NOLINT
{
    return sf::Mouse::getPosition(window);
}
