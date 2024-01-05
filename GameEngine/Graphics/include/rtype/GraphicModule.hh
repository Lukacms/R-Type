//
// Created by kane on 14/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <csignal>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/InputManager.hpp>
#include <rtype/SparseArray.hpp>
#include <string_view>

namespace rtype
{
    const constexpr int STANDARD_WIDTH{800};
    const constexpr int STANDARD_HEIGHT{600};
    const constexpr char *STANDARD_TITLE{"R-TYPE"};

    struct Vector2D {
            int x{-1};
            int y{-1};
    };

    enum class Key {
        ZERO = 0,
        ONE = 1,
        TWO = 2,
        TRHEE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        DOT = 10,
        DEL = 11,
        ESC = 12,
        ENTER = 13,
        NONE = 14,
        MAX_KEY = 15
    };

    struct KeyMap {
            Key key{rtype::Key::NONE};
            char chr{0};
    };

    static const constexpr std::array<KeyMap, static_cast<size_t>(rtype::Key::MAX_KEY)> KEY_MAP{{
        {rtype::Key::ZERO, '0'},
        {rtype::Key::ONE, '1'},
        {rtype::Key::TWO, '2'},
        {rtype::Key::TRHEE, '3'},
        {rtype::Key::FOUR, '4'},
        {rtype::Key::FIVE, '5'},
        {rtype::Key::SIX, '6'},
        {rtype::Key::SEVEN, '7'},
        {rtype::Key::EIGHT, '8'},
        {rtype::Key::NINE, '9'},
        {rtype::Key::DOT, '.'},
        {rtype::Key::DEL, 127},
        {rtype::Key::ESC, 27},
        {rtype::Key::ENTER, '\n'},
        {rtype::Key::NONE, '\0'},
    }};

    class GraphicModule
    {
        public:
            explicit GraphicModule(unsigned int width = STANDARD_WIDTH,
                                   unsigned int height = STANDARD_HEIGHT,
                                   const std::string &title = STANDARD_TITLE);
            ~GraphicModule() = default;
            GraphicModule(const GraphicModule &) = delete;
            GraphicModule(GraphicModule &&) = delete;
            GraphicModule &operator=(const GraphicModule &) = delete;
            GraphicModule &operator=(GraphicModule &&) = delete;

            void update();
            void draw_components(SparseArray<SpriteComponent> sprites,
                                 SparseArray<rtype::TransformComponent> transforms);
            void draw(sf::Sprite &sprite, rtype::TransformComponent transform);
            void draw(sf::Text &text);
            void display();
            void close_window();
            void clear();
            void close();
            Vector2D is_mouse_button_pressed();
            bool is_input_pressed(rtype::Key key);
            bool is_input_pressed(sf::Keyboard::Key key);
            [[nodiscard]] bool is_window_open();

        private:
            sf::VideoMode m_mode;
            sf::RenderWindow m_window;
            InputManager m_input{};
    };
} // namespace rtype
