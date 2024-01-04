/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** transform_system
*/

#include <iomanip>
#include <iostream>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>

namespace rtype
{
    void transform_system(ComponentManager &registry, float delta_time)
    {
        SparseArray<TransformComponent> &transforms = registry.get_components<TransformComponent>();

        for (auto &transform : transforms) {
            if (transform == std::nullopt)
                continue;
            transform->position_x += transform->velocity_x * delta_time;
            transform->position_y += transform->velocity_y * delta_time;
            DEBUG(("--------------------------------------------------"));
            DEBUG(("Delta_Time = %f\n", static_cast<double>(delta_time)));
            DEBUG(("VELOCITY : %f:%f\n", static_cast<double>(transform->velocity_x * delta_time),
                   static_cast<double>(transform->velocity_y * delta_time)));
            DEBUG(("POSITION : %f:%f\n", static_cast<double>(transform->position_x),
                   static_cast<double>(transform->position_y)));
            DEBUG(("--------------------------------------------------"));
        }
    }
} // namespace rtype
