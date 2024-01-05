/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#include <array>
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

    m_host.setFont(m_font);
    m_host.setString(" ");
    m_host.setCharacterSize(18);
    m_host.setFillColor(sf::Color::Black);

    m_port.setFont(m_font);
    m_port.setString(" ");
    m_port.setCharacterSize(18);
    m_port.setFillColor(sf::Color::Black);

    m_transforms[0].scale_x = static_cast<float>(width) / MENU_BG_WIDTH;
    m_transforms[0].scale_y = static_cast<float>(height) / MENU_BG_HEIGHT;
    m_transforms[1].position_x = static_cast<float>(m_width) / MIDLE_DIV;
    m_transforms[1].position_y = POS_Y_TEXT_MENU;
    m_transforms[2].position_x = static_cast<float>(m_width) / 5.0F;
    m_transforms[2].position_y = static_cast<float>(m_height) / 2.0F;
    m_transforms[3].position_x = static_cast<float>(m_width) / 1.35F;
    m_transforms[3].position_y = static_cast<float>(m_height) / 2.0F;
    m_text.setPosition(static_cast<float>(m_width) / MIDLE_DIV,
                       static_cast<float>(m_height) / TEXT_HEIGHT_DIV);
}

void rclient::Menu::launch(dl::DlLoader<rtype::GraphicModule> &graphical_module, std::string &host,
                           std::string &port)
{
    bool start_cut_scene{false};
    while (graphical_module.get_class().is_window_open() && !m_changing_scene) {
        graphical_module.get_class().update();
        if (graphical_module.get_class().is_input_pressed(rtype::Key::ENTER)) {
            start_cut_scene = true;
            m_timer_menu = std::chrono::steady_clock::now();
        }
        if (start_cut_scene) {
            m_changing_scene = true;
        }
        animate();
        button_handling(graphical_module);
        key_handling(graphical_module);
        draw(graphical_module);
    }
}

void rclient::Menu::draw(dl::DlLoader<rtype::GraphicModule> &graphical_module)
{

    sf::Sprite sprite{};
    graphical_module.get_class().clear();
    for (size_t i{0}; i < 2; i++) {
        if (i == 0)
            sprite.setScale(m_transforms[0].scale_x, m_transforms[0].scale_y);
        if (i == 1) {
            sprite.setScale(1, 1);
            sprite.setOrigin(LOGO_ORIGIN_X, 0);
        }
        m_texture.loadFromFile(m_paths[i]);
        sprite.setPosition(m_transforms[i].position_x, m_transforms[i].position_y);
        sprite.setTexture(m_texture);
        graphical_module.get_class().draw(sprite, {});
    }
    for (size_t i{2}; i < 4; i++) {
        m_texture.loadFromFile("./assets/text_box.png");
        sprite.setPosition(m_transforms[i].position_x, m_transforms[i].position_y);
        sf::Rect rect{0, 0, 0, 0};
        rect.width = 601;
        rect.height = 211;
        sprite.setTextureRect(rect);
        sprite.setScale(0.3F, 0.3F);
        sprite.setTexture(m_texture);
        graphical_module.get_class().draw(sprite, {});
        if (i == 2)
            m_left_box = sprite.getGlobalBounds();
        if (i == 3)
            m_right_box = sprite.getGlobalBounds();
    }
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

void rclient::Menu::button_handling(dl::DlLoader<rtype::GraphicModule> &graphical_module)
{
    rtype::Vector2D mouse_pos{graphical_module.get_class().is_mouse_button_pressed()};

    if (mouse_pos.x == -1 && mouse_pos.y == -1)
        return;
    std::cout << mouse_pos.x << ' ' << mouse_pos.y << '\n';
    if (m_left_box.contains(mouse_pos.x, mouse_pos.y)) {
        m_select_host = true;
        m_select_port = false;
        std::cout << "left\n";
    }
    if (m_right_box.contains(mouse_pos.x, mouse_pos.y)) {
        m_select_host = false;
        m_select_port = true;
        std::cout << "right\n";
    }
}

void rclient::Menu::key_handling(dl::DlLoader<rtype::GraphicModule> &graphical_module)
{
    char tmp{'\0'};

    for (size_t i{0}; i < rtype::KEY_MAP.size(); i++) {
        if (graphical_module.get_class().is_input_pressed(rtype::KEY_MAP[i].key))
            tmp = rtype::KEY_MAP[i].chr;
    }
    if (m_clock.get_elapsed_time_in_ms() < 200)
        return;
    m_clock.reset();
    if (m_select_host) {
        std::cout << m_host_str << '\n';
        if (tmp == 127 && !m_host_str.empty())
            m_host_str.erase(m_host_str.end() - 1);
        if (tmp == '\n')
            m_select_host = false;
        if ((tmp >= 48 && tmp <= 57) || tmp == '.')
            m_host_str.push_back(tmp);
    }
    if (m_select_port) {
        if (tmp == 127 && !m_port_str.empty())
            m_port_str.erase(m_host_str.end() - 1);
        if (tmp == '\n')
            m_select_host = false;
        if ((tmp >= 48 && tmp <= 57) || tmp == '.')
            m_port_str.push_back(tmp);
    }
}
