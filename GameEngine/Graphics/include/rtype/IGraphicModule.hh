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
#include <string>

namespace rtype
{

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
            virtual void draw(rtype::TextComponent &text, rtype::TransformComponent &transform) = 0;
            virtual void draw(rtype::SpriteComponent &sprite,
                              rtype::TransformComponent &transform) = 0;
            virtual float get_text_width(rtype::TextComponent &text) = 0;
            virtual void display() = 0;
            virtual void close_window() = 0;
            virtual void clear() = 0;
            virtual bool is_input_pressed(rtype::Keys key) = 0;
            [[nodiscard]] virtual bool is_window_open() = 0;
    };
} // namespace rtype
