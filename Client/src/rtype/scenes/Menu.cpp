/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#include <ios>
#include <rtype/scenes/IScene.hh>
#include <rtype/scenes/Menu.hh>

rclient::scenes::Menu::Menu(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
    for (size_t i{0}; i < 3; i++) {
        m_clocks[i] = std::chrono::steady_clock::now();
    }
    m_text.text = "Press Enter to play";
    m_text.colors = {255, 255, 255, 255};
    m_text.font_path = "./assets/font.ttf";
    m_text.font_size = PLAY_FONT_SIZE;
    m_sprites[0].texture_path = "./assets/SpaceBG.png";
    m_sprites[0].origin = {0, 0};
    m_sprites[1].texture_path = "./assets/Rtype-logo2.png";
    m_sprites[1].origin = {LOGO_ORIGIN_X, 0};
    m_transforms[0].scale_x = static_cast<float>(width) / MENU_BG_WIDTH;
    m_transforms[0].scale_y = static_cast<float>(height) / MENU_BG_HEIGHT;
    m_transforms[1].position_x = m_width / MIDLE_DIV;
    m_transforms[1].position_y = POS_Y_TEXT_MENU;
    m_transforms[4].position_x = static_cast<float>(m_width) / MIDLE_DIV;
    m_transforms[4].position_y = static_cast<float>(m_height) / TEXT_HEIGHT_DIV;
}

void rclient::scenes::Menu::display(rtype::IGraphicModule &graphics)
{
    graphics.clear();
    animate();
    for (size_t i{0}; i < 2; i++) {
        graphics.draw(m_sprites[i], m_transforms[i]);
    }
    m_text.origin = {graphics.get_text_width(m_text) / 2.0F, 0};
    graphics.draw(m_text, m_transforms[4]);
    graphics.display();
}

void rclient::scenes::Menu::handle_events(rtype::IGraphicModule &graphics, State &state)
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
        auto color = m_text.colors;

        if (color.opacity < MAX_OPACITY_TEXT_MENU && !m_fading_text)
            m_text.colors.opacity += OPACITY_INCREMENTATION;
        if (color.opacity >= MAX_OPACITY_TEXT_MENU && !m_fading_text)
            m_fading_text = true;
        if (color.opacity > MIN_OPACITY_TEXT_MENU && m_fading_text)
            m_text.colors.opacity -= OPACITY_INCREMENTATION;
        if (color.opacity <= MIN_OPACITY_TEXT_MENU && m_fading_text)
            m_fading_text = false;
    }
}

void rclient::scenes::Menu::cut_scene_handling()
{
}

void rclient::scenes::Menu::handle_network(ntw::Communication & /* commn */, State & /* state */)
{
}

void rclient::scenes::Menu::button_handling(rtype::IGraphicModule &graphical_module)
{
    /*    rtype::Vector2D mouse_pos{graphical_module.get_class().is_mouse_button_pressed()};

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
        */
}

void rclient::scenes::Menu::key_handling(rtype::IGraphicModule &graphical_module)
{
    /*
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
    */
}
