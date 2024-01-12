//
// Created by kane on 14/12/23.
//

#include <iostream>
#include <rtype/SFML/SFMLGraphicModule.hh>
#include <rtype/utils/Vector2D.hpp>

rtype::SFMLGraphicModule::SFMLGraphicModule(unsigned int width, unsigned int height,
                                            const std::string &title)
    : m_mode{width, height}, m_window{m_mode, title}
{
}

void rtype::SFMLGraphicModule::draw_components(SparseArray<rtype::SpriteComponent> &sprites,
                                               SparseArray<rtype::TransformComponent> &transforms)
{
    sf::Sprite sprite{};

    for (size_t index = 0; index < sprites.size(); index += 1) {
        if (!sprites[index].has_value())
            continue;
        try {
            auto &texture = m_texture_library.get_texture(sprites[index]->texture_path);
            sprite.setPosition(transforms[index]->position_x, transforms[index]->position_y);
            sprite.setTextureRect({sprites[index]->rectangle.x, sprites[index]->rectangle.y,
                                   sprites[index]->rectangle.width,
                                   sprites[index]->rectangle.height});
            sprite.setOrigin(sprites[index]->origin.x, sprites[index]->origin.y);
            sprite.setScale(transforms[index]->scale_x, transforms[index]->scale_y);
            sprite.setTexture(texture.texture);
            sprite.setColor({255, 255, 255, static_cast<sf::Uint8>(sprites[index]->opacity)});
            m_window.draw(sprite);
        } catch (rtype::TextureLibrary::TextureException &e) {
            std::cerr << "R-Type : Texture " << sprites[index]->texture_path << " not found"
                      << std::endl;
            continue;
        }
    }
}

void rtype::SFMLGraphicModule::display()
{
    m_window.display();
}

void rtype::SFMLGraphicModule::clear()
{
    m_window.clear();
}

bool rtype::SFMLGraphicModule::is_window_open()
{
    return m_window.isOpen();
}

void rtype::SFMLGraphicModule::close_window()
{
    m_window.close();
}

bool rtype::SFMLGraphicModule::is_input_pressed(rtype::Keys key)
{
    if (key == rtype::Keys::DOWN)
        printf("");
    for (const auto &keyring : KEYS_ARRAY) {
        if (keyring.key == key)
            return m_input.is_key_pressed(keyring.sfml_key);
    }
    return false;
}

void rtype::SFMLGraphicModule::update()
{
    sf::Event evt;

    m_input.update();
    while (m_window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed)
            m_window.close();
    }
}

void rtype::SFMLGraphicModule::draw(rtype::SpriteComponent &sprite_component,
                                    rtype::TransformComponent transform)
{
    sf::Sprite sprite{};

    try {
        auto &texture = m_texture_library.get_texture(sprite_component.texture_path);
        sprite.setPosition(transform.position_x, transform.position_y);
        sprite.setTextureRect({sprite_component.rectangle.x, sprite_component.rectangle.y,
                               sprite_component.rectangle.width,
                               sprite_component.rectangle.height});
        sprite.setOrigin(sprite_component.origin.x, sprite_component.origin.y);
        sprite.setScale(transform.scale_x, transform.scale_y);
        sprite.setTexture(texture.texture);
        sprite.setColor({255, 255, 255, static_cast<sf::Uint8>(sprite_component.opacity)});
        m_window.draw(sprite);
    } catch (rtype::TextureLibrary::TextureException &e) {
        std::cerr << "R-Type : Texture " << sprite_component.texture_path << " not found"
                  << std::endl;
    }
}

void rtype::SFMLGraphicModule::draw(sf::Sprite &sprite_component,
                                    rtype::TransformComponent transform)
{
    sprite_component.setPosition(transform.position_x, transform.position_y);
    sprite_component.setScale(transform.scale_x, transform.scale_y);
    m_window.draw(sprite_component);
}

void rtype::SFMLGraphicModule::draw(sf::Text &text, rtype::TransformComponent transform)
{
    text.setPosition(transform.position_x, transform.position_y);
    m_window.draw(text);
}

rtype::utils::Vector2D<float> rtype::SFMLGraphicModule::is_left_mouse_pressed()
{
    if (m_input.is_mouse_button_pressed(sf::Mouse::Button::Left)) {
        auto click{m_input.get_mouse_position(m_window)};
        return {static_cast<float>(click.x), static_cast<float>(click.y)};
    }
    return {-1, -1};
}

void rtype::SFMLGraphicModule::set_view_port(sf::View &view)
{
    m_window.setView(view);
}

sf::View rtype::SFMLGraphicModule::get_view_port()
{
    return m_window.getView();
}
