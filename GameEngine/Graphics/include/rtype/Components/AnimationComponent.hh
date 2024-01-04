/*
** EPITECH PROJECT, 2023
** Graphics
** File description:
** AnimationComponent
*/

#pragma once

#include "rtype/utils/Clock.hh"
#include "rtype/utils/Vector2D.hh"
#include <vector>

namespace rtype
{
    struct AnimationClip {
            std::string animation_name;
            bool is_loop{false};
            double time_after_change;
            std::vector<rtype::utils::TextureRect> texture_rects;
    };

    struct AnimationComponent {
            std::size_t current_frame{0};
            std::string current_animation{};
            rtype::utils::Clock clock;
            std::vector<AnimationClip> animation_clips{};
    };
} // namespace rtype
