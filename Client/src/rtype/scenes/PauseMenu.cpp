/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** PauseMenu
*/

#include "rtype/scenes/IScene.hh"
#include <iostream>
#include <rtype/scenes/PauseMenu.hh>

rclient::scenes::PauseMenu::PauseMenu(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
    for (size_t i{0}; i < 3; i++) {
        m_clocks[i] = std::chrono::steady_clock::now();
    }
    m_texts[0].colors = {255, 255, 255, 255};
    m_texts[0].text = "Press Enter to continue";
    m_texts[0].font_path = "./assets/font.ttf";
    m_texts[0].font_size = PLAY_FONT_SIZE;

    m_texts[1].colors = {255, 255, 255, 255};
    m_texts[1].text = "Press M to mute";
    m_texts[1].font_path = "./assets/font.ttf";
    m_texts[1].font_size = PLAY_FONT_SIZE;

    m_texts[2].colors = {255, 255, 255, 255};
    m_texts[2].text = "Press U to unmute";
    m_texts[2].font_path = "./assets/font.ttf";
    m_texts[2].font_size = PLAY_FONT_SIZE;

    m_texts[3].colors = {255, 255, 255, 255};
    m_texts[3].text = "Press Q to quit";
    m_texts[3].font_path = "./assets/font.ttf";
    m_texts[3].font_size = PLAY_FONT_SIZE;

    m_sprites[0].texture_path = "./assets/SpaceBG.png";
    m_sprites[1].texture_path = "./assets/Rtype-logo2.png";
    m_sprites[1].origin = {LOGO_ORIGIN_X, 0};

    m_transforms[0].scale_x = static_cast<float>(width) / MENU_BG_WIDTH;
    m_transforms[0].scale_y = static_cast<float>(height) / MENU_BG_HEIGHT;

    m_transforms[1].position_x = m_width / MIDLE_DIV;
    m_transforms[1].position_y = POS_Y_TEXT_MENU;

    m_texts_transforms[0] = {.position_x = static_cast<float>(m_width) / MIDLE_DIV,
                             .position_y =
                                 static_cast<float>(m_height) / TEXT_HEIGHT_DIV - TEXT_BASE};

    m_texts_transforms[1] = {.position_x = static_cast<float>(m_width) / MIDLE_DIV,
                             .position_y =
                                 static_cast<float>(m_height) / TEXT_HEIGHT_DIV - MUTE_BASE};

    m_texts_transforms[2] = {.position_x = static_cast<float>(m_width) / MIDLE_DIV,
                             .position_y =
                                 static_cast<float>(m_height) / TEXT_HEIGHT_DIV - UNMUTE_BASE};

    m_texts_transforms[3] = {.position_x = static_cast<float>(m_width) / MIDLE_DIV,
                             .position_y =
                                 static_cast<float>(m_height) / TEXT_HEIGHT_DIV - TEXT_HEIGHT_DIV};
}

void rclient::scenes::PauseMenu::display(rtype::IGraphicModule &graphics)
{
    for (size_t i{0}; i < 2; i++)
        graphics.draw(m_sprites[i], m_transforms[i]);
    for (size_t i{0}; i < 4; i++) {
        if (m_texts[i].origin.x < 0.1f && m_texts[i].origin.y > -0.1F)
            m_texts[i].origin = {graphics.get_text_width(m_texts[i]) / 2.0F, 0};
        graphics.draw(m_texts[i], m_texts_transforms[i]);
    }

    graphics.display();
}

void rclient::scenes::PauseMenu::handle_events(rtype::IGraphicModule &graphics, State &state)
{
    if (graphics.is_input_pressed(rtype::Keys::ENTER))
        state = State::Game;
}

void rclient::scenes::PauseMenu::handle_network(ntw::Communication & /* commn */,
                                                State & /* state */)
{
}
