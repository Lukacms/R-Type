/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** transform_component
*/

#pragma once

#include <nlohmann/json.hpp>

namespace rtype
{
    struct TransformComponent {
        public:
            /* variables */
            float position_x{0};
            float position_y{0};
            float velocity_x{0};
            float velocity_y{0};
            float scale_x{1};
            float scale_y{1};
            float rotation{0};

            TransformComponent(float position_x = 0, float position_y = 0, float velocity_x = 0,
                               float velocity_y = 0, float scale_x = 1, float scale_y = 1,
                               float rotation = 1);
            /* njson */
            TransformComponent &operator=(const nlohmann::json &json);
            TransformComponent(const nlohmann::json &json);
    };
} // namespace rtype
