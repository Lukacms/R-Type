//
// Created by kane on 14/12/23.
//

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <array>
#include <rtype/GraphicModule.hh>

rtype::GraphicModule::GraphicModule(unsigned int width, unsigned int height,
                                    const std::string &title)
    : m_mode{width, height}, m_window{m_mode, title}
{
}

void rtype::GraphicModule::draw_components(SparseArray<rtype::SpriteComponent> sprites,
                                           SparseArray<rtype::TransformComponent> transforms)
{
    sf::Texture texture{};

    for (size_t index = 0; index < sprites.size(); index += 1) {
        if (!sprites[index].has_value())
            continue;
        texture.loadFromFile(sprites[index]->texture_path);
        sprites[index]->sprite.setPosition(transforms[index]->position_x,
                                           transforms[index]->position_y);
        sprites[index]->sprite.setTexture(texture);
        m_window.draw(sprites[index]->sprite);
    }
}

void rtype::GraphicModule::draw(sf::Sprite &sprite, TransformComponent /* transform */)
{
    m_window.draw(sprite);
}

void rtype::GraphicModule::draw(sf::Text &text)
{
    m_window.draw(text);
}

void rtype::GraphicModule::display()
{
    m_window.display();
}

void rtype::GraphicModule::clear()
{
    m_window.clear();
}

bool rtype::GraphicModule::is_window_open()
{
    return m_window.isOpen();
}

void rtype::GraphicModule::close_window()
{
    m_window.close();
}

bool rtype::GraphicModule::is_input_pressed(sf::Keyboard::Key key)
{
    return m_input.is_key_pressed(key);
}

bool rtype::GraphicModule::is_input_pressed(rtype::Key key)
{
    static const constexpr std::array<sf::Keyboard::Key, static_cast<size_t>(rtype::Key::MAX_KEY)>
        key_map{sf::Keyboard::Key::Num0,   sf::Keyboard::Key::Num1,   sf::Keyboard::Key::Num2,
                sf::Keyboard::Key::Num3,   sf::Keyboard::Key::Num4,   sf::Keyboard::Key::Num5,
                sf::Keyboard::Key::Num6,   sf::Keyboard::Key::Num7,   sf::Keyboard::Key::Num8,
                sf::Keyboard::Key::Num9,   sf::Keyboard::Key::Period, sf::Keyboard::Key::Delete,
                sf::Keyboard::Key::Escape, sf::Keyboard::Key::Enter,  sf::Keyboard::Key::Unknown};
    return m_input.is_key_pressed(key_map[static_cast<size_t>(key)]);
}

void rtype::GraphicModule::update()
{
    sf::Event evt{};

    m_input.update();
    while (m_window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed)
            m_window.close();
    }
}

void rtype::GraphicModule::close()
{
    m_window.close();
}

rtype::Vector2D rtype::GraphicModule::is_mouse_button_pressed()
{
    if (m_input.is_mouse_button_pressed(sf::Mouse::Button::Left)) {
        auto tmp{m_input.get_mouse_position(m_window)};
        return {tmp.x, tmp.y};
    }
    return {};
}
