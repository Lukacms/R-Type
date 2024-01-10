/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>
#include <rtype/utils/Vector2D.hpp>

namespace rtype
{
    struct KeyInput {
        sf::Keyboard::Key key;
        bool is_pressed{false};
    };

    class InputManager
    {
        public:
            InputManager();
            ~InputManager() = default;
            InputManager(const InputManager &) = default;
            InputManager(InputManager &&) = default;
            InputManager &operator=(const InputManager &) = default;
            InputManager &operator=(InputManager &&) = default;

            void update();
            bool is_key_pressed(sf::Keyboard::Key key) const;
            bool is_mouse_button_pressed(sf::Mouse::Button button) const;
            sf::Vector2i get_mouse_position(const sf::Window &window) const;

        private:
            void update_joystick();

            std::vector<KeyInput> m_key_mapping{};
            std::unordered_map<sf::Mouse::Button, bool> mouseButtonMap{};
            rtype::utils::Vector2D<float> m_joystick{};
    };
} // namespace rtype
