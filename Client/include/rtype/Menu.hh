/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#pragma once

#include <chrono>
#include <rtype/GraphicModule.hh>
#include <rtype/dlloader/DlLoader.hpp>

namespace rclient
{
    static const constexpr int PLAY_FONT_SIZE{28};
    static const constexpr int LOGO_ORIGIN_X{250};
    static const constexpr float MIDLE_DIV{2.0F};
    static const constexpr float TEXT_HEIGHT_DIV{1.5F};
    static const constexpr float POS_Y_TEXT_MENU{50};
    static const constexpr double CLOCK_TIMER_LOGO{250};
    static const constexpr int LOGO_MAX_Y{60};
    static const constexpr int LOGO_MIN_Y{40};
    static const constexpr double CLOCK_TIMER_TEXT_MENU{50};
    static const constexpr int MAX_OPACITY_TEXT_MENU{250};
    static const constexpr int MIN_OPACITY_TEXT_MENU{50};
    static const constexpr int OPACITY_INCREMENTATION{5};
    static const constexpr float MENU_BG_WIDTH{1000.0F};
    static const constexpr float MENU_BG_HEIGHT{562.0F};

    class Menu
    {
        public:
            explicit Menu(unsigned int width, unsigned int height, const std::string &title);
            Menu(Menu const &to_copy) = delete;
            Menu(Menu &&to_move) = delete;
            ~Menu() = default;
            Menu &operator=(Menu const &to_copy) = delete;
            Menu &operator=(Menu &&to_move) = delete;

            void launch();

        private:
            bool m_changing_scene{false};
            bool m_descending_logo{false};
            bool m_fading_text{false};
            unsigned int m_width{};
            unsigned int m_height{};

            std::chrono::time_point<std::chrono::steady_clock> m_timer_menu;
            dl::DlLoader<rtype::GraphicModule> m_graphical_module;
            std::array<std::chrono::time_point<std::chrono::steady_clock>, 3> m_clocks{};
            sf::Texture m_texture{};
            std::array<rtype::TransformComponent, 2> m_transforms{};
            std::array<std::string, 2> m_paths{"./assets/SpaceBG.png", "./assets/Rtype-logo2.png"};

            sf::Font m_font{};
            sf::Sprite m_sprite{};
            sf::Text m_text{};

            void draw();
            void animate();
            void cut_scene_handling();
    };
} // namespace rclient
