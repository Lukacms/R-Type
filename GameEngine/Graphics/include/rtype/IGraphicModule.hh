//
// Created by kane on 04/01/24.
//

#pragma once

#include "rtype/Components/TextComponent.hh"
#include <SFML/Graphics/Sprite.hpp>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Keys.hh>
#include <rtype/SparseArray.hpp>
#include <rtype/utils/Vector2D.hpp>
#include <string>
#include <string_view>

namespace rtype
{
    constexpr unsigned int STANDARD_WIDTH{800};
    constexpr unsigned int STANDARD_HEIGHT{600};
    constexpr std::string_view STANDARD_TITLE{"R-TYPE"};

    class IGraphicModule
    {
        public:
            IGraphicModule() = default;
            virtual ~IGraphicModule() = default;
            IGraphicModule(const IGraphicModule &) = delete;
            IGraphicModule(IGraphicModule &&) = delete;
            IGraphicModule &operator=(const IGraphicModule &) = delete;
            IGraphicModule &operator=(IGraphicModule &&) = delete;

            virtual void update() = 0;
            virtual void draw_components(SparseArray<rtype::SpriteComponent> &sprites,
                                         SparseArray<rtype::TransformComponent> &transforms) = 0;
            virtual void draw_components(SparseArray<rtype::TextComponent> &sprites,
                                         SparseArray<rtype::TransformComponent> &transforms) = 0;
            virtual void draw(rtype::TextComponent &text,
                              const rtype::TransformComponent &transform) = 0;
            virtual void draw(rtype::SpriteComponent &sprite,
                              const rtype::TransformComponent &transform) = 0;
            virtual void draw(sf::Sprite &sprite, const rtype::TransformComponent &transform) = 0;
            virtual void draw(sf::Text &text_component, const TransformComponent &transform) = 0;
            virtual float get_text_width(rtype::TextComponent &text) = 0;
            virtual bool is_sprite_left_click(rtype::SpriteComponent &sprite,
                                              rtype::TransformComponent &transform) = 0;
            virtual void set_view_port(sf::View &) = 0;
            [[nodiscard]] virtual sf::View get_view_port() = 0;
            virtual void display() = 0;
            virtual void close_window() = 0;
            virtual void clear() = 0;
            virtual bool is_input_pressed(rtype::Keys key) = 0;
            [[nodiscard]] virtual bool is_window_open() = 0;
            [[nodiscard]] virtual rtype::utils::Vector2D<float> is_left_mouse_pressed() = 0;
    };
} // namespace rtype
