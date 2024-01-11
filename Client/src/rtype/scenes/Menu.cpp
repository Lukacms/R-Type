/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#include <fstream>
#include <nlohmann/json.hpp>
#include <rtype/Keys.hh>
#include <rtype/SFML/SFMLGraphicModule.hh>
#include <rtype/scenes/Game.hh>
#include <rtype/scenes/IScene.hh>
#include <rtype/scenes/Menu.hh>

rclient::scenes::Menu::Menu(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
    for (size_t i{0}; i < 3; i++) {
        m_clocks[i] = std::chrono::steady_clock::now();
    }
    m_texts[0].text = "Press Enter to play";
    m_texts[0].colors = {255, 255, 255, 255};
    m_texts[0].font_path = "./assets/font.ttf";
    m_texts[0].font_size = PLAY_FONT_SIZE;

    m_texts[1].text = "";
    m_texts[1].colors = {255, 255, 255, 255};
    m_texts[1].font_path = "./assets/font.ttf";
    m_texts[1].font_size = 20;

    m_texts[2].text = "";
    m_texts[2].colors = {255, 255, 255, 255};
    m_texts[2].font_path = "./assets/font.ttf";
    m_texts[2].font_size = 20;

    m_texts[3].text = "Press S to see the Scoreboard";
    m_texts[3].colors = {0, 0, 0, 255};
    m_texts[3].font_path = "./assets/font.ttf";
    m_texts[3].font_size = PLAY_FONT_SIZE;

    m_sprites[0].texture_path = "./assets/SpaceBG.png";
    m_sprites[0].origin = {0, 0};
    m_sprites[1].texture_path = "./assets/Rtype-logo2.png";
    m_sprites[1].origin = {LOGO_ORIGIN_X, 0};

    m_sprites[2].texture_path = "./assets/button.png";
    m_sprites[2].origin = {100, 50};
    m_sprites[2].rectangle.width = 200;
    m_sprites[2].rectangle.height = 100;

    m_sprites[3].texture_path = "./assets/High_score/full_score_window.png";
    m_sprites[3].origin = {100, 50};
    m_sprites[3].rectangle.width = 390;
    m_sprites[3].rectangle.height = 450;

    m_sprites[4].texture_path = "./assets/High_score/icon1.png";
    m_sprites[4].origin = {100, 50};
    m_sprites[4].rectangle.width = 95;
    m_sprites[4].rectangle.height = 95;

    m_sprites[5].texture_path = "./assets/High_score/icon2.png";
    m_sprites[5].origin = {100, 50};
    m_sprites[5].rectangle.width = 95;
    m_sprites[5].rectangle.height = 95;

    m_sprites[6].texture_path = "./assets/High_score/icon3.png";
    m_sprites[6].origin = {100, 50};
    m_sprites[6].rectangle.width = 95;
    m_sprites[6].rectangle.height = 95;


    m_transforms[0].scale_x = static_cast<float>(width) / MENU_BG_WIDTH;
    m_transforms[0].scale_y = static_cast<float>(height) / MENU_BG_HEIGHT;

    m_transforms[1].position_x = m_width / MIDLE_DIV;
    m_transforms[1].position_y = POS_Y_TEXT_MENU;

    m_transforms[2].position_x = m_width / 5.0F;
    m_transforms[2].position_y = m_height / 2.0F;

    m_transforms[3].position_x = m_width / 1.2F;
    m_transforms[3].position_y = m_height / 2.0F;

    m_transforms[4].position_x = static_cast<float>(m_width) / MIDLE_DIV;
    m_transforms[4].position_y = static_cast<float>(m_height) / TEXT_HEIGHT_DIV;

    m_transforms[5].position_x = m_transforms[4].position_x - 200.0F;
    m_transforms[5].position_y = m_transforms[4].position_y + 100.0F;

    m_transforms[6].position_x = m_transforms[1].position_x - 100.0F;
    m_transforms[6].position_y = m_transforms[1].position_y + 100.0F;
}

void rclient::scenes::Menu::display(rtype::IGraphicModule &graphics)
{
    graphics.clear();
    animate();
    for (size_t i{0}; i < 2; i++) {
        graphics.draw(m_sprites[i], m_transforms[i]);
        graphics.draw(m_sprites[2], m_transforms[2 + i]);
    }
    m_texts[0].origin = {graphics.get_text_width(m_texts[0]) / 2.0F, 0};
    button_handling(graphics);
    key_handling(graphics);
    graphics.draw(m_texts[0], m_transforms[4]);
    auto tmp_transform_1 = m_transforms[2];
    tmp_transform_1.position_x -= 50;
    tmp_transform_1.position_y -= 20;
    auto tmp_transform_2 = m_transforms[3];
    tmp_transform_2.position_x -= 50;
    tmp_transform_2.position_y -= 20;
    graphics.draw(m_texts[1], tmp_transform_1);
    graphics.draw(m_texts[2], tmp_transform_2);
    graphics.draw(m_texts[3], m_transforms[5]);
    if (graphics.MENU_PRESSED == true) {
        graphics.draw(m_sprites[3], m_transforms[6]);
        std::ifstream file("./scoreboards/score1.json");
        nlohmann::json j;
        file >> j;
        std::string tmp;
        if (m_texts[5].text.empty()) {
            int i = 0;
            for (auto &it : j.items()) {
                std::cout << it.value()["name"] << std::endl;
                tmp = it.value()["name"];
                tmp += " : ";
                tmp += std::to_string(static_cast<int>(it.value()["score"]));
                m_texts[4 + i].text = tmp;
                m_texts[4 + i].colors = {255, 255, 255, 255};
                m_texts[4 + i].font_path = "./assets/font.ttf";
                m_texts[4 + i].font_size = 20;
                m_transforms[7 + i].position_x = m_transforms[6].position_x + 55.0F;
                m_transforms[7 + i].position_y = m_transforms[6].position_y + 70.0F + (i * 113);
                m_transforms[10+i].position_x = m_transforms[7].position_x - 10.0F; 
                m_transforms[10+i].position_y = m_transforms[6].position_y + 82.0F +(i * 112);
                i++;
            }
        }
        for (int i = 0; i < 3; i++) {
            graphics.draw(m_texts[4 + i], m_transforms[7 + i]);
            graphics.draw(m_sprites[4 + i], m_transforms[10+i]);
        }
    }
    this->animate();
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
            m_transforms[1].position_y += 1;
        }
        if (m_transforms[1].position_y > LOGO_MAX_Y && !m_descending_logo)
            m_descending_logo = true;
        if (m_transforms[1].position_y >= LOGO_MIN_Y && m_descending_logo) {
            m_transforms[1].position_y -= 1;
        }
        if (m_transforms[1].position_y < LOGO_MIN_Y && m_descending_logo)
            m_descending_logo = false;
    }
    if (static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::steady_clock::now() - m_clocks[1])
                                .count()) > CLOCK_TIMER_TEXT_MENU) {
        m_clocks[1] = now;
        auto color = m_texts[0].colors;

        if (color.opacity < MAX_OPACITY_TEXT_MENU && !m_fading_text)
            m_texts[0].colors.opacity += OPACITY_INCREMENTATION;
        if (color.opacity >= MAX_OPACITY_TEXT_MENU && !m_fading_text)
            m_fading_text = true;
        if (color.opacity > MIN_OPACITY_TEXT_MENU && m_fading_text)
            m_texts[0].colors.opacity -= OPACITY_INCREMENTATION;
        if (color.opacity <= MIN_OPACITY_TEXT_MENU && m_fading_text)
            m_fading_text = false;

        if (color.opacity < MAX_OPACITY_TEXT_MENU && !m_fading_text)
            m_texts[3].colors.opacity += OPACITY_INCREMENTATION;
        if (color.opacity >= MAX_OPACITY_TEXT_MENU && !m_fading_text)
            m_fading_text = true;
        if (color.opacity > MIN_OPACITY_TEXT_MENU && m_fading_text)
            m_texts[3].colors.opacity -= OPACITY_INCREMENTATION;
        if (color.opacity <= MIN_OPACITY_TEXT_MENU && m_fading_text)
            m_fading_text = false;
    }
}

void rclient::scenes::Menu::cut_scene_handling()
{
}

void rclient::scenes::Menu::handle_network(ntw::Communication & /* commn */,
                                           rtype::IAudioModule & /*audio*/, State & /* state */)
{
}

void rclient::scenes::Menu::button_handling(rtype::IGraphicModule &graphical_module)
{
    if (graphical_module.is_sprite_left_click(m_sprites[2], m_transforms[2])) {
        m_left_selected = false;
        m_right_selected = true;
    }
    if (graphical_module.is_sprite_left_click(m_sprites[2], m_transforms[3])) {
        m_right_selected = false;
        m_left_selected = true;
    }
}

void rclient::scenes::Menu::key_handling(rtype::IGraphicModule &graphical_module)
{
    char tmp{'\0'};
    if (m_inputs_clock.get_elapsed_time_in_ms() < 150)
        return;

    m_inputs_clock.reset();
    if (graphical_module.is_input_pressed(rtype::Keys::S))
        graphical_module.MENU_PRESSED = !graphical_module.MENU_PRESSED;

    if (graphical_module.is_input_pressed(rtype::Keys::ZERO))
        tmp = '0';
    if (graphical_module.is_input_pressed(rtype::Keys::ONE))
        tmp = '1';
    if (graphical_module.is_input_pressed(rtype::Keys::TWO))
        tmp = '2';
    if (graphical_module.is_input_pressed(rtype::Keys::THREE))
        tmp = '3';
    if (graphical_module.is_input_pressed(rtype::Keys::FOUR))
        tmp = '4';
    if (graphical_module.is_input_pressed(rtype::Keys::FIVE))
        tmp = '5';
    if (graphical_module.is_input_pressed(rtype::Keys::SIX))
        tmp = '6';
    if (graphical_module.is_input_pressed(rtype::Keys::SEVEN))
        tmp = '7';
    if (graphical_module.is_input_pressed(rtype::Keys::EIGHT))
        tmp = '8';
    if (graphical_module.is_input_pressed(rtype::Keys::NINE))
        tmp = '9';
    if (graphical_module.is_input_pressed(rtype::Keys::DOT))
        tmp = '.';
    if (graphical_module.is_input_pressed(rtype::Keys::DELETE)) {
        tmp = 127;
    }
    if (m_right_selected) {
        if (tmp == 127 && !m_texts[1].text.empty())
            m_texts[1].text.erase(m_texts[1].text.end() - 1);
        else if (tmp != '\0')
            m_texts[1].text.push_back(tmp);
    }
    if (m_left_selected) {
        if (tmp == 127 && !m_texts[2].text.empty())
            m_texts[2].text.erase(m_texts[2].text.end() - 1);
        else if (tmp != '\0')
            m_texts[2].text.push_back(tmp);
    }
}
