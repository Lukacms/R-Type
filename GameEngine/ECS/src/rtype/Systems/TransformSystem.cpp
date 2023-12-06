/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** transform_system
*/

#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>

namespace rtype
{
    void transform_system(Registry &registry)
    {
        SparseArray<TransformComponent> &transforms = registry.get_components<TransformComponent>();
        float delta_time = 0.1F;

        for (auto &transform : transforms) {
            if (transform == std::nullopt)
                continue;
            transform->position_x += transform->velocity_x * delta_time;
            transform->position_y += transform->velocity_y * delta_time;
        }
    }
} // namespace rtype
