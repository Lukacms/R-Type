/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#pragma once

#include <chrono>
#include <functional>
#include <rtype/GraphicModule.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/scenes/IScene.hh>

namespace rclient::scenes
{
    class Menu : public IScene
    {
        public:
            Menu(unsigned int width = STANDARD_WIDTH, unsigned int height = STANDARD_HEIGHT);
            Menu(Menu const &to_copy) = delete;
            Menu(Menu &&to_move) = delete;
            ~Menu() override = default;
            Menu &operator=(Menu const &to_copy) = delete;
            Menu &operator=(Menu &&to_move) = delete;

            void display(rtype::GraphicModule &graphical_module) override;
            void handle_events(rtype::GraphicModule &graphics, State &state) override;
            void handle_network(ntw::Communication &commn, State &state) override;

        private:
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

            void animate();
            void cut_scene_handling();
    };

} // namespace rclient::scenes
