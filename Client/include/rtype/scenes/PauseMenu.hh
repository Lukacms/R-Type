/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** PauseMenu
*/

#pragma once

#include <chrono>
#include <functional>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/scenes/IScene.hh>
#include <rtype/scenes/Menu.hh>

namespace rclient::scenes
{
    constexpr int TEXT_BASE{150};
    constexpr int MUTE_BASE{100};
    constexpr int UNMUTE_BASE{50};

    class PauseMenu : public IScene
    {
        public:
            PauseMenu(unsigned int width = rtype::STANDARD_WIDTH,
                      unsigned int height = rtype::STANDARD_HEIGHT);
            PauseMenu(PauseMenu const &to_copy) = delete;
            PauseMenu(PauseMenu &&to_move) = delete;
            ~PauseMenu() override = default;
            PauseMenu &operator=(PauseMenu const &to_copy) = delete;
            PauseMenu &operator=(PauseMenu &&to_move) = delete;

            void display(rtype::IGraphicModule &graphics) override;
            void handle_events(rtype::IGraphicModule &graphics, State &state) override;
            void handle_network(ntw::Communication &commn, State &state) override;

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

            void cut_scene_handling();
    };

} // namespace rclient::scenes
