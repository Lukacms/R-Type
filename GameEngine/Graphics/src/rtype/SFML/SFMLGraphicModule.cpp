//
// Created by kane on 14/12/23.
//

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <rtype/Components/TextComponent.hh>
#include <rtype/Components/TransformComponent.hh>
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
    sf::Texture texture{};
    sf::Sprite sprite{};

    for (size_t index = 0; index < sprites.size(); index += 1) {
        if (!sprites[index].has_value())
            continue;
        texture.loadFromFile(sprites[index]->texture_path);
        sprite.setPosition(transforms[index]->position_x, transforms[index]->position_y);
        sprite.setTextureRect({sprites[index]->rectangle.x, sprites[index]->rectangle.y,
                               sprites[index]->rectangle.width, sprites[index]->rectangle.height});
        sprite.setOrigin(sprites[index]->origin.x, sprites[index]->origin.y);
        sprite.setScale(transforms[index]->scale_x, transforms[index]->scale_y);
        sprite.setTexture(texture);
        m_window.draw(sprite);
    }
}

void rtype::SFMLGraphicModule::draw_components(SparseArray<rtype::TextComponent> &texts,
                                               SparseArray<rtype::TransformComponent> &transforms)
{
    sf::Font font{};
    sf::Text text{};
    sf::Color colors{};

    for (size_t index = 0; index < texts.size(); index += 1) {
        if (!texts[index].has_value())
            continue;
        font.loadFromFile(texts[index]->font_path);
        text.setFont(font);
        text.setString(texts[index]->text);
        text.setOrigin(texts[index]->origin.x, texts[index]->origin.y);
        text.setCharacterSize(texts[index]->font_size);
        colors.a = texts[index]->colors.opacity;
        colors.r = texts[index]->colors.red;
        colors.g = texts[index]->colors.green;
        colors.b = texts[index]->colors.blue;
        text.setFillColor(colors);
        text.setPosition(transforms[index]->position_x, transforms[index]->position_y);
        text.setScale(transforms[index]->scale_x, transforms[index]->scale_y);
        m_window.draw(text);
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
                                    const rtype::TransformComponent &transform)
{
    sf::Texture texture{};
    sf::Sprite sprite{};

    texture.loadFromFile(sprite_component.texture_path);
    sprite.setPosition(transform.position_x, transform.position_y);
    sprite.setTextureRect({sprite_component.rectangle.x, sprite_component.rectangle.y,
                           sprite_component.rectangle.width, sprite_component.rectangle.height});
    sprite.setOrigin(sprite_component.origin.x, sprite_component.origin.y);
    sprite.setScale(transform.scale_x, transform.scale_y);
    sprite.setTexture(texture);
    m_window.draw(sprite);
}

void rtype::SFMLGraphicModule::draw(sf::Sprite &sprite, const rtype::TransformComponent &transform)
{
    sprite.setPosition(transform.position_x, transform.position_y);
    sprite.setScale(transform.scale_x, transform.scale_y);
    m_window.draw(sprite);
}

void rtype::SFMLGraphicModule::draw(sf::Text &text, const rtype::TransformComponent &transform)
{

    text.setPosition({transform.position_x, transform.position_y});
    text.setScale({transform.scale_x, transform.scale_y});
    m_window.draw(text);
}

void rtype::SFMLGraphicModule::draw(rtype::TextComponent &text_component,
                                    const rtype::TransformComponent &transform)
{
    sf::Font font{};
    sf::Text text{};
    sf::Color colors{};

    font.loadFromFile(text_component.font_path);
    text.setFont(font);
    text.setString(text_component.text);
    text.setOrigin(text_component.origin.x, text_component.origin.y);
    text.setCharacterSize(text_component.font_size);
    colors.a = text_component.colors.opacity;
    colors.r = text_component.colors.red;
    colors.g = text_component.colors.green;
    colors.b = text_component.colors.blue;
    text.setFillColor(colors);
    text.setPosition(transform.position_x, transform.position_y);
    m_window.draw(text);
}

float rtype::SFMLGraphicModule::get_text_width(rtype::TextComponent &text_component)
{
    sf::Text text{};
    sf::Font font{};

    font.loadFromFile(text_component.font_path);
    text.setFont(font);
    text.setString(text_component.text);
    text.setCharacterSize(text_component.font_size);
    return text.getGlobalBounds().width;
}

bool rtype::SFMLGraphicModule::is_sprite_left_click(rtype::SpriteComponent &sprite,
                                                    rtype::TransformComponent &transform)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return false;

    auto mouse_pos{sf::Mouse::getPosition(m_window)};
    sf::Sprite tmp_sprite{};
    sf::Texture tmp_texture{};
    sf::IntRect tmp_rect{};

    tmp_texture.loadFromFile(sprite.texture_path);
    tmp_sprite.setPosition(transform.position_x, transform.position_y);
    tmp_sprite.setOrigin(sprite.origin.x, sprite.origin.y);
    tmp_rect.width = sprite.rectangle.width;
    tmp_rect.left = sprite.rectangle.x;
    tmp_rect.top = sprite.rectangle.y;
    tmp_rect.height = sprite.rectangle.height;
    tmp_sprite.setTextureRect(tmp_rect);
    tmp_sprite.setTexture(tmp_texture);
    sf::FloatRect sprite_pos{tmp_sprite.getGlobalBounds()};

    return sprite_pos.contains(mouse_pos.x, mouse_pos.y);
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
