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
    void transform_system(ComponentManager &registry, float /* delta_time */)
    {
        SparseArray<TransformComponent> &transforms{registry.get_components<TransformComponent>()};

        for (auto &transform : transforms) {
            if (transform == std::nullopt)
                continue;
            transform->position_x += transform->velocity_x;
            transform->position_y += transform->velocity_y;
        }
    }
} // namespace rtype
