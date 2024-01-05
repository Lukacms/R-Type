/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** PauseMenu
*/

#pragma once

#include <chrono>
#include <functional>
#include <rtype/GraphicModule.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/scenes/Menu.hh>

namespace rclient::scenes
{

    class PauseMenu
    {
        public:
            explicit PauseMenu(unsigned int width, unsigned int height);
            PauseMenu(PauseMenu const &to_copy) = delete;
            PauseMenu(PauseMenu &&to_move) = delete;
            ~PauseMenu() = default;
            PauseMenu &operator=(PauseMenu const &to_copy) = delete;
            PauseMenu &operator=(PauseMenu &&to_move) = delete;

            void launch(dl::DlLoader<rtype::GraphicModule> &graphical_module);

        private:
            bool m_changing_scene{false};
            bool m_descending_logo{false};
            bool m_fading_text{false};
            unsigned int m_width{};
            unsigned int m_height{};

            std::chrono::time_point<std::chrono::steady_clock> m_timer_menu;
            std::array<std::chrono::time_point<std::chrono::steady_clock>, 3> m_clocks{};
            sf::Texture m_texture{};
            std::array<rtype::TransformComponent, 2> m_transforms{};
            std::array<std::string, 2> m_paths{"./assets/SpaceBG.png", "./assets/Rtype-logo2.png"};

            sf::Font m_font{};
            sf::Sprite m_sprite{};
            sf::Text m_text{};
            sf::Text m_mute{};
            sf::Text m_unmute{};
            sf::Text m_quit{};

            void draw(dl::DlLoader<rtype::GraphicModule> &graphical_modules);
            void cut_scene_handling();
    };

} // namespace rclient::scenes
