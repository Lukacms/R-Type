/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** PauseMenu
*/

#pragma once

#include <rtype/Components/TextComponent.hh>
#include <rtype/IGraphicModule.hh>
#include <array>
#include <chrono>
#include <functional>
#include <rtype/IAudioModule.hh>
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
            void handle_events(rtype::IGraphicModule &graphics, rtype::IAudioModule &audio,
                               State &state) override;
            void handle_network(ntw::Communication &commn, rtype::IAudioModule &audio,
                                State &state) override;

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
            std::array<rtype::TextComponent, 4> m_texts{};
            std::array<rtype::SpriteComponent, 2> m_sprites{};
            std::array<rtype::TransformComponent, 4> m_texts_transforms{};

            void cut_scene_handling();
    };

} // namespace rclient::scenes
