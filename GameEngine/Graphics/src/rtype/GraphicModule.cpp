//
// Created by kane on 14/12/23.
//

#include <rtype/GraphicModule.hh>

rtype::GraphicModule::GraphicModule(unsigned int width, unsigned int height,
                                    const std::string &title)
    : m_mode{{width, height}}, m_window{m_mode, title}
{
}

void rtype::GraphicModule::draw_components(SparseArray<rtype::SpriteComponent> sprites)
{
    for (auto &sprite : sprites) {
        if (sprite.has_value())
            m_window.draw(sprite.value().sprite);
    }
}

void rtype::GraphicModule::draw(sf::Sprite &sprite)
{
    m_window.draw(sprite);
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

bool rtype::GraphicModule::is_input_pressed(sf::Keyboard::Key key)
{
    return m_input.is_key_pressed(key);
}

void rtype::GraphicModule::update()
{
    m_input.update();
}
