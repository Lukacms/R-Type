/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#pragma once

#include "rtype/Components/SpriteComponent.hh"
#include "rtype/Components/TextComponent.hh"
#include "rtype/Components/TransformComponent.hh"
#include "rtype/utils/Clock.hh"
#include <chrono>
#include <functional>
#include <rtype/IAudioModule.hh>
#include <rtype/SFML/SFMLGraphicModule.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/scenes/IScene.hh>

namespace rclient::scenes
{
    class Menu : public IScene
    {
        public:
            Menu(unsigned int width = rtype::STANDARD_WIDTH,
                 unsigned int height = rtype::STANDARD_HEIGHT);
            Menu(Menu const &to_copy) = delete;
            Menu(Menu &&to_move) = delete;
            ~Menu() override = default;
            Menu &operator=(Menu const &to_copy) = delete;
            Menu &operator=(Menu &&to_move) = delete;

            void display(rtype::IGraphicModule &graphics) override;
            void handle_events(rtype::IGraphicModule &graphics, rtype::IAudioModule &audio,
                               State &state) override;
            void handle_network(ntw::Communication &commn, rtype::IAudioModule &audio,
                                State &state) override;

        private:
            bool m_descending_logo{false};
            bool m_fading_text{false};
            bool m_left_selected{false};
            bool m_right_selected{false};
            bool s_selected{false};
            unsigned int m_width{};
            unsigned int m_height{};

            rtype::utils::Clock m_inputs_clock{};
            std::array<std::chrono::time_point<std::chrono::steady_clock>, 3> m_clocks{};
            std::array<rtype::TransformComponent, 13> m_transforms{};
            std::array<rtype::SpriteComponent, 7> m_sprites{};
            std::array<rtype::TextComponent, 7> m_texts{};

            void animate();
            void cut_scene_handling();
            void button_handling(rtype::IGraphicModule &graphical_module);
            void key_handling(rtype::IGraphicModule &graphical_module);
    };

} // namespace rclient::scenes
