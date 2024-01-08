/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** transform_component
*/

#pragma once

namespace rtype
{
    struct TransformComponent {
        public:
            float position_x{0};
            float position_y{0};
            float velocity_x{0};
            float velocity_y{0};
            float scale_x{1};
            float scale_y{1};
    };
} // namespace rtype
