/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** inputManager
*/

#pragma once

#include <SFML/Window.hpp>
#include <rtype/utils/Vector2D.hpp>
#include <unordered_map>

namespace rtype
{
    struct KeyInput {
            sf::Keyboard::Key key;
            bool is_pressed{false};
    };

    constexpr float JOYSTICK_INPUT{50.0F};

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
            [[nodiscard]] bool is_key_pressed(sf::Keyboard::Key key) const;
            [[nodiscard]] bool is_mouse_button_pressed(sf::Mouse::Button button) const;
            [[nodiscard]] sf::Vector2i get_mouse_position(const sf::Window &window) const;

        private:
            void update_joystick();

            std::vector<KeyInput> m_key_mapping{};
            rtype::utils::Vector2D<float> m_joystick{};
            std::unordered_map<sf::Mouse::Button, bool> mouse_button_map{};
    };
} // namespace rtype
