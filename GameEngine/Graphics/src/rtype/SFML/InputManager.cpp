/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#include <rtype/SFML/InputManager.hh>


rtype::InputManager::InputManager()
{
    for (int key = sf::Keyboard::Key::A; key != sf::Keyboard::KeyCount; ++key)
        m_key_mapping.emplace_back(static_cast<sf::Keyboard::Key>(key), false);
}

void rtype::InputManager::update()
{
    for (auto &key : m_key_mapping)
        key.is_pressed = sf::Keyboard::isKeyPressed(key.key);
    if (sf::Joystick::isConnected(0)) {
        sf::Joystick::update();
        update_joystick();
    }
    for (int button{static_cast<int>(sf::Mouse::Button::Left)}; button != sf::Mouse::ButtonCount;
         ++button) {
        mouseButtonMap[static_cast<sf::Mouse::Button>(button)] =
            sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }
}

bool rtype::InputManager::is_key_pressed(sf::Keyboard::Key key) const
{
    for (const auto &keyring : m_key_mapping)
        if (static_cast<sf::Keyboard::Key>(keyring.key) == key)
            return keyring.is_pressed;
}

bool rtype::InputManager::is_mouse_button_pressed(sf::Mouse::Button button) const
{
    auto input = mouseButtonMap.find(button);

    if (input != mouseButtonMap.end()) {
        return input->second;
    }
    return false;
}

sf::Vector2i rtype::InputManager::get_mouse_position(const sf::Window &window) const // NOLINT
{
    return sf::Mouse::getPosition(window);
}

void rtype::InputManager::update_joystick()
{
    for (auto &keyring : m_key_mapping) {
        if (keyring.key == sf::Keyboard::Up && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 50.F)
            keyring.is_pressed = true;
        if (keyring.key == sf::Keyboard::Down && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > -50.F)
            keyring.is_pressed = true;
        if (keyring.key == sf::Keyboard::Right && sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50.F)
            keyring.is_pressed = true;
        if (keyring.key == sf::Keyboard::Left && sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50.F)
            keyring.is_pressed = true;
        if (keyring.key == sf::Keyboard::W && (sf::Joystick::isButtonPressed(0, 7) || sf::Joystick::isButtonPressed(0, 1)))
            keyring.is_pressed = true;
        if (keyring.key == sf::Keyboard::Enter && sf::Joystick::isButtonPressed(0, 10))
            keyring.is_pressed = true;
        if (keyring.key == sf::Keyboard::Escape && sf::Joystick::isButtonPressed(0, 9))
            keyring.is_pressed = true;
    }
}
