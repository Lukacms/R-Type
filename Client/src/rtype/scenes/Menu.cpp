/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#include <rtype/scenes/Menu.hh>

rclient::scenes::Menu::Menu(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
    for (size_t i{0}; i < 3; i++) {
        m_clocks[i] = std::chrono::steady_clock::now();
    }
    m_font.loadFromFile("./assets/font.ttf");
    m_text.setFont(m_font);
    m_text.setString("Press Enter to play");
    m_text.setCharacterSize(PLAY_FONT_SIZE);
    m_text.setFillColor(sf::Color::White);
    m_text.setOrigin(m_text.getGlobalBounds().width / 2, 0);
    m_transforms[0].scale_x = static_cast<float>(width) / MENU_BG_WIDTH;
    m_transforms[0].scale_y = static_cast<float>(height) / MENU_BG_HEIGHT;
    m_transforms[1].position_x = m_width / MIDLE_DIV;
    m_transforms[1].position_y = POS_Y_TEXT_MENU;
    m_text.setPosition(static_cast<float>(m_width) / MIDLE_DIV,
                       static_cast<float>(m_height) / TEXT_HEIGHT_DIV);
}

void rclient::scenes::Menu::display(rtype::IGraphicModule &graphics)
{
    graphics.clear();
    animate();
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
    graphics.draw(
        m_text,
        {static_cast<float>(m_width) / MIDLE_DIV, static_cast<float>(m_height) / TEXT_HEIGHT_DIV});
    graphics.display();
}

void rclient::scenes::Menu::handle_events(rtype::IGraphicModule &graphics,
                                          rtype::IAudioModule & /*audio*/, State &state)
{
    if (graphics.is_input_pressed(rtype::Keys::ESCAPE))
        state = State::Lounge;
}

void rclient::scenes::Menu::animate() // NOLINT
{
    auto now = std::chrono::steady_clock::now();

    if (static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::steady_clock::now() - m_clocks[0])
                                .count()) > CLOCK_TIMER_LOGO) {
        m_clocks[0] = now;
        if (m_transforms[1].position_y <= LOGO_MAX_Y && !m_descending_logo) {
            m_transforms[1].position_y += 2;
        }
        if (m_transforms[1].position_y > LOGO_MAX_Y && !m_descending_logo)
            m_descending_logo = true;
        if (m_transforms[1].position_y >= LOGO_MIN_Y && m_descending_logo) {
            m_transforms[1].position_y -= 2;
        }
        if (m_transforms[1].position_y < LOGO_MIN_Y && m_descending_logo)
            m_descending_logo = false;
    }
    if (static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::steady_clock::now() - m_clocks[1])
                                .count()) > CLOCK_TIMER_TEXT_MENU) {
        m_clocks[1] = now;
        auto color = m_text.getFillColor();
        if (color.a < MAX_OPACITY_TEXT_MENU && !m_fading_text)
            color.a += OPACITY_INCREMENTATION;
        if (color.a >= MAX_OPACITY_TEXT_MENU && !m_fading_text)
            m_fading_text = true;
        if (color.a > MIN_OPACITY_TEXT_MENU && m_fading_text)
            color.a -= OPACITY_INCREMENTATION;
        if (color.a <= MIN_OPACITY_TEXT_MENU && m_fading_text)
            m_fading_text = false;
        m_text.setFillColor(color);
    }
}

void rclient::scenes::Menu::cut_scene_handling()
{
}

void rclient::scenes::Menu::handle_network(ntw::Communication & /* commn */,
                                           rtype::IAudioModule & /*audio*/, State & /* state */)
{
}
