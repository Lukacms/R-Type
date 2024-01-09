//
// Created by kane on 14/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/IGraphicModule.hh>
#include <rtype/Keys.hh>
#include <rtype/SFML/InputManager.hh>
#include <rtype/SparseArray.hpp>

namespace rtype
{
    struct SFMLKeyring {
            sf::Keyboard::Key sfml_key;
            rtype::Keys key;
    };

    static const std::array<SFMLKeyring, 8> KEYS_ARRAY{{
        {sf::Keyboard::Up, rtype::Keys::UP},
        {sf::Keyboard::Right, rtype::Keys::RIGHT},
        {sf::Keyboard::Down, rtype::Keys::DOWN},
        {sf::Keyboard::Left, rtype::Keys::LEFT},
        {sf::Keyboard::Enter, rtype::Keys::ENTER},
        {sf::Keyboard::Escape, rtype::Keys::ESCAPE},
        {sf::Keyboard::Q, rtype::Keys::Q},
        {sf::Keyboard::W, rtype::Keys::W},
    }};

    void animation_system(ComponentManager &registry, float /* delta_time */);

    class SFMLGraphicModule : public rtype::IGraphicModule
    {
        public:
            SFMLGraphicModule(unsigned int width = STANDARD_WIDTH,
                              unsigned int height = STANDARD_HEIGHT,
                              const std::string &title = STANDARD_TITLE.data());
            ~SFMLGraphicModule() override = default;
            SFMLGraphicModule(const SFMLGraphicModule &) = delete;
            SFMLGraphicModule(SFMLGraphicModule &&) = delete;
            SFMLGraphicModule &operator=(const SFMLGraphicModule &) = delete;
            SFMLGraphicModule &operator=(SFMLGraphicModule &&) = delete;

            void update() final;
            void draw_components(SparseArray<SpriteComponent> &sprites,
                                 SparseArray<TransformComponent> &transforms) final;
            void draw(SpriteComponent &sprite, rtype::TransformComponent transform) final;
            void draw(sf::Sprite &sprite, rtype::TransformComponent transform) final;
            void draw(sf::Text &text, rtype::TransformComponent transform) final;
            void display() final;
            void close_window() final;
            void clear() final;
            bool is_input_pressed(rtype::Keys key) final;
            [[nodiscard]] bool is_window_open() final;

        private:
            sf::VideoMode m_mode;
            sf::RenderWindow m_window;
            InputManager m_input{};
    };
} // namespace rtype
