/*
** EPITECH PROJECT, 2023
** Graphics
** File description:
** AnimationComponent
*/

#pragma once

#include <vector>

namespace rtype
{

    struct AnimationComponent {
            double timer{0};
            std::vector<int> left_rect_pos{};
    };

} // namespace rtype
