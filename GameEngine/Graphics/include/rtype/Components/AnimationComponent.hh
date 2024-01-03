/*
** EPITECH PROJECT, 2023
** Graphics
** File description:
** AnimationComponent
*/

#pragma once

#include <rtype/utils/Clock.hh>
#include <vector>

namespace rtype
{
    struct TextureRect {
            int x{0};
            int y{0};
            int width{0};
            int height{0};
    };

    struct AnimationClip {
            std::string animation_name;
            bool is_loop{false};
            double time_after_change;
            std::vector<TextureRect> texture_rects;
    };

    struct AnimationComponent {
            std::size_t current_frame{0};
            std::string current_animation{};
            rtype::utils::Clock clock;
            std::vector<AnimationClip> animation_clips{};
    };
} // namespace rtype
