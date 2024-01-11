//
// Created by kane on 11/01/24.
//

#include <fstream>
#include <iostream>
#include <rtype/Background/BackgroundManager.hh>

rclient::BackgroundManager::BackgroundManager()
{
    m_backgrounds[0].transform = rtype::TransformComponent{0, 0, 0, 0, 1, 1};
    m_backgrounds[0].sprite =
        rtype::SpriteComponent{{0, 0, BG_SIZE, BG_SIZE}, BG_BASE.data(), {0, 0}};
    m_backgrounds[1].transform = rtype::TransformComponent{BG_SIZE, 0, 0, 0, 1, 1};
    m_backgrounds[1].sprite =
        rtype::SpriteComponent{{0, 0, BG_SIZE, BG_SIZE}, BG_BASE.data(), {0, 0}};

    std::ifstream bg_file(BG_JSON_PATH.data());

    if (!bg_file.is_open()) {
        std::cerr << "Cannot load textures because texture file doesn't exist" << std::endl;
        throw std::exception();
    }
    auto textures = njson::parse(bg_file);

    for (const auto &[key, value] : textures.items()) {
        auto &new_texture = m_rectangles.emplace_back();
        new_texture.name = key;
        new_texture.rectangle = rtype::utils::TextureRect{value["textureRect"]};
    }
}

void rclient::BackgroundManager::change_background(std::string &name)
{
    if (name == m_new_background)
        return;
    is_fading_in = true;
    m_new_background = name;
}

std::array<rclient::BackgroundSpecifier, 2> rclient::BackgroundManager::get_backgrounds() const
{
    return m_backgrounds;
}

void rclient::BackgroundManager::update()
{
    for (std::size_t index = 0; index < m_backgrounds.size(); index += 1) {
        if (m_backgrounds[index].transform.position_x + BG_SIZE < 0)
            m_backgrounds[index].transform.position_x =
                m_backgrounds[(index + 1) % m_backgrounds.size()].transform.position_x + BG_SIZE;
        m_backgrounds[index].transform.position_x -= 2;
    }
    if (m_backgrounds[0].sprite.opacity < 255 || m_current_background != m_new_background)
        handle_change();
}

void rclient::BackgroundManager::handle_change()
{
    if (is_fading_in && m_backgrounds[0].sprite.opacity > 5) {
        m_backgrounds[0].sprite.opacity -= 5;
        m_backgrounds[1].sprite.opacity -= 5;
    }
    if (is_fading_in && m_backgrounds[0].sprite.opacity <= 5) {
        is_fading_in = false;
        for (auto &bg : m_rectangles) {
            if (bg.name == m_new_background) {
                m_backgrounds[0].sprite.rectangle = bg.rectangle;
                m_backgrounds[1].sprite.rectangle = bg.rectangle;
            }
        }
    }
    if (!is_fading_in && m_backgrounds[0].sprite.opacity < 250) {
        m_backgrounds[0].sprite.opacity += 5;
        m_backgrounds[1].sprite.opacity += 5;
    }
    if (!is_fading_in && m_backgrounds[0].sprite.opacity >= 250)
        m_current_background = m_new_background;
}
