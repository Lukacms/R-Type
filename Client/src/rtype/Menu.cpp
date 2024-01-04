/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#include <rtype/Menu.hh>

rclient::Menu::Menu(unsigned int width, unsigned int height) : m_width(width), m_height(height)
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

void rclient::Menu::launch(dl::DlLoader<rtype::GraphicModule> &graphical_module)

{
    bool start_cut_scene{false};
    while (graphical_module.get_class().is_window_open() && !m_changing_scene) {
        graphical_module.get_class().update();
        if (graphical_module.get_class().is_input_pressed(sf::Keyboard::Enter)) {
            start_cut_scene = true;
            m_timer_menu = std::chrono::steady_clock::now();
        }
        if (start_cut_scene) {
            m_changing_scene = true;
        }
        animate();
        draw(graphical_module);
    }
}

void rclient::Menu::draw(dl::DlLoader<rtype::GraphicModule> &graphical_module)
{
    graphical_module.get_class().clear();
    for (size_t i{0}; i < 2; i++) {
        if (i == 0)
            m_sprite.setScale(m_transforms[0].scale_x, m_transforms[0].scale_y);
        if (i == 1)
            m_sprite.setOrigin(LOGO_ORIGIN_X, 0);
        m_texture.loadFromFile(m_paths[i]);
        m_sprite.setPosition(m_transforms[i].position_x, m_transforms[i].position_y);
        m_sprite.setTexture(m_texture);
        graphical_module.get_class().draw(m_sprite, {});
    }
    m_sprite.setOrigin(0, 0);
    m_sprite.setScale(1, 1);
    graphical_module.get_class().draw(m_text);
    graphical_module.get_class().display();
}

void rclient::Menu::animate() // NOLINT
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

void rclient::Menu::cut_scene_handling()
{
}

rclient::PauseMenu::PauseMenu(unsigned int width, unsigned int height)
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
    m_text.setPosition(static_cast<float>(m_width) / MIDLE_DIV,
                       static_cast<float>(m_height) / TEXT_HEIGHT_DIV - 150);
    m_mute.setPosition(static_cast<float>(m_width) / MIDLE_DIV,
                       static_cast<float>(m_height) / TEXT_HEIGHT_DIV - 100);
    m_unmute.setPosition(static_cast<float>(m_width) / MIDLE_DIV,
                         static_cast<float>(m_height) / TEXT_HEIGHT_DIV - 50);
    m_quit.setPosition(static_cast<float>(m_width) / MIDLE_DIV,
                       static_cast<float>(m_height) / TEXT_HEIGHT_DIV);
}

void rclient::PauseMenu::launch(dl::DlLoader<rtype::GraphicModule> &graphical_module)

{
    bool start_cut_scene{false};
    while (graphical_module.get_class().is_window_open() && !m_changing_scene) {
        graphical_module.get_class().update();
        if (graphical_module.get_class().is_input_pressed(sf::Keyboard::Enter)) {
            start_cut_scene = true;
            m_timer_menu = std::chrono::steady_clock::now();
            std::cout << "Enter pressed" << std::endl;
        }
        if (graphical_module.get_class().is_input_pressed(sf::Keyboard::M)) {
            std::cout << "M pressed" << std::endl;
            // m_audio_manager.setVolume("test", 0);
            // TODO : Mute
        }
        if (graphical_module.get_class().is_input_pressed(sf::Keyboard::U)) {
            std::cout << "U pressed" << std::endl;
            // m_audio_manager.setVolume("test", 100);
            // TODO : Unmute
        }
        if (graphical_module.get_class().is_input_pressed(sf::Keyboard::Q)) {
            graphical_module.get_class().close();
            // TODO : Close also client
        }
        if (start_cut_scene) {
            m_changing_scene = true;
        }
        draw(graphical_module);
    }
}

void rclient::PauseMenu::draw(dl::DlLoader<rtype::GraphicModule> &graphical_module)
{
    graphical_module.get_class().clear();
    for (size_t i{0}; i < 2; i++) {
        if (i == 0)
            m_sprite.setScale(m_transforms[0].scale_x, m_transforms[0].scale_y);
        if (i == 1)
            m_sprite.setOrigin(LOGO_ORIGIN_X, 0);
        m_texture.loadFromFile(m_paths[i]);
        m_sprite.setPosition(m_transforms[i].position_x, m_transforms[i].position_y);
        m_sprite.setTexture(m_texture);
        graphical_module.get_class().draw(m_sprite, {});
    }
    m_sprite.setOrigin(0, 0);
    m_sprite.setScale(1, 1);
    graphical_module.get_class().draw(m_text);
    graphical_module.get_class().draw(m_mute);
    graphical_module.get_class().draw(m_unmute);
    graphical_module.get_class().draw(m_quit);
    graphical_module.get_class().display();
}
