//
// Created by kane on 14/12/23.
//

#include <iostream>
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

void rtype::GraphicModule::draw(sf::Sprite &sprite, TransformComponent transform)
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
    sf::Event evt;

    m_input.update();
    while (m_window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed)
            m_window.close();
    }
}
