/*
** EPITECH PROJECT, 2023
** Components
** File description:
** HeathComposant
*/

#pragma once

#include <nlohmann/json.hpp>

namespace rtype
{

    struct HealthComponent {
        public:
            /* variables */
            int health{0};
            int max_health{0};

            HealthComponent(int phealth = 0, int pmax_health = 0);
            /* njson */
            HealthComponent &operator=(const nlohmann::json &json);
            HealthComponent(const nlohmann::json &json);
    };

}; // namespace rtype
