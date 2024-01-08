/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** PauseMenu
*/

#include <iostream>
#include <rtype/scenes/PauseMenu.hh>

rclient::scenes::PauseMenu::PauseMenu(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
    for (size_t i{0}; i < 3; i++) {
        m_clocks[i] = std::chrono::steady_clock::now();
    }
    m_font.loadFromFile("./assets/font.ttf");
    m_text.setFont(m_font);
    m_text.setString("Press Enter to continue");
    m_text.setCharacterSize(PLAY_FONT_SIZE);
    m_text.setFillColor(sf::Color::White);
    m_text.setOrigin(m_text.getGlobalBounds().width / 2, 0);

    m_mute.setFont(m_font);
    m_mute.setString("Press M to mute");
    m_mute.setCharacterSize(PLAY_FONT_SIZE);
    m_mute.setFillColor(sf::Color::White);
    m_mute.setOrigin(m_mute.getGlobalBounds().width / 2, 0);

    m_unmute.setFont(m_font);
    m_unmute.setString("Press U to unmute");
    m_unmute.setCharacterSize(PLAY_FONT_SIZE);
    m_unmute.setFillColor(sf::Color::White);
    m_unmute.setOrigin(m_unmute.getGlobalBounds().width / 2, 0);

    m_quit.setFont(m_font);
    m_quit.setString("Press Q to quit");
    m_quit.setCharacterSize(PLAY_FONT_SIZE);
    m_quit.setFillColor(sf::Color::White);
    m_quit.setOrigin(m_quit.getGlobalBounds().width / 2, 0);

    m_transforms[0].scale_x = static_cast<float>(width) / MENU_BG_WIDTH;
    m_transforms[0].scale_y = static_cast<float>(height) / MENU_BG_HEIGHT;
    m_transforms[1].position_x = m_width / MIDLE_DIV;
    m_transforms[1].position_y = POS_Y_TEXT_MENU;
}

void rclient::scenes::PauseMenu::display(rtype::IGraphicModule &graphics)
{
    std::cout << "ouin\n";
    graphics.clear();
    for (size_t i{0}; i < 2; i++) {
        if (i == 0)
            m_sprite.setScale(m_transforms[0].scale_x, m_transforms[0].scale_y);
        if (i == 1)
            m_sprite.setOrigin(LOGO_ORIGIN_X, 0);
        m_texture.loadFromFile(m_paths[i]);
        m_sprite.setTexture(m_texture);
        graphics.draw(m_sprite, m_transforms[i]);
    }
    m_sprite.setOrigin(0, 0);
    m_sprite.setScale(1, 1);
    graphics.draw(m_text,
                  rtype::TransformComponent{
                      .position_x = static_cast<float>(m_width) / MIDLE_DIV,
                      .position_y = static_cast<float>(m_height) / TEXT_HEIGHT_DIV - TEXT_BASE});
    graphics.draw(m_mute,
                  rtype::TransformComponent{
                      .position_x = static_cast<float>(m_width) / MIDLE_DIV,
                      .position_y = static_cast<float>(m_height) / TEXT_HEIGHT_DIV - MUTE_BASE});
    graphics.draw(m_unmute,
                  rtype::TransformComponent{
                      .position_x = static_cast<float>(m_width) / MIDLE_DIV,
                      .position_y = static_cast<float>(m_height) / TEXT_HEIGHT_DIV - UNMUTE_BASE});
    graphics.draw(
        m_quit,
        rtype::TransformComponent{.position_x = static_cast<float>(m_width) / MIDLE_DIV,
                                  .position_y = static_cast<float>(m_height) / TEXT_HEIGHT_DIV});
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
