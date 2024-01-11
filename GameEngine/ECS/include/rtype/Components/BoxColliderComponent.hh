//
// Created by kane on 11/12/23.
//

#pragma once

#include <nlohmann/json.hpp>

namespace rtype
{
    struct BoxColliderComponent {
        public:
            /* variables */
            float width;
            float height;

            BoxColliderComponent(float pwidth = 0, float pheigth = 0);
            /* njson */
            BoxColliderComponent(const nlohmann::json &json);
            BoxColliderComponent &operator=(const nlohmann::json &json);
    };
} // namespace rtype
