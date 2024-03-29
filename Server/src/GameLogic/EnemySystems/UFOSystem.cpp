/*
** EPITECH PROJECT, 2023
** EnemySystems
** File description:
** UFOSystem
*/

#include <algorithm>
#include <cmath>
#include <rtype/ComponentManager.hpp>
#include <rtype/Components/ClockComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>

namespace rserver::game
{
    /**
     * @brief used by ufo_system to determine the movement of the entity
     *
     * @param x_wave - float
     * @return - float
     */
    static float sinus_wave(float x_wave)
    {
        return 100 * std::sin(x_wave / 50);
    }

    /**
     * @brief UFO System for the ufo enemy, that moves like a «snake», with sinusoidal functions
     *
     * @param registry ComponentManager
     */
    void ufo_system(rtype::ComponentManager &registry, float /* delta_time */)
    {
        auto &clocks = registry.get_components<rtype::ClockComponent>();
        auto &transforms = registry.get_components<rtype::TransformComponent>();
        auto &tags = registry.get_components<rtype::TagComponent>();

        for (std::size_t entity = 0; entity < tags.size(); entity += 1) {
            if (!tags[entity].has_value() || tags[entity]->tag != "UFOEnemy")
                continue;
            if (!clocks[entity].has_value() || !transforms[entity].has_value())
                continue;
            transforms[entity]->position_y += sinus_wave(transforms[entity]->position_x) / 20;
        }
    }
} // namespace rserver::game
