//
// Created by kane on 11/12/23.
//

#include <iostream>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>

namespace rtype
{
    void collider_system(ComponentManager &registry, [[maybe_unused]] float delta_time)
    {
        SparseArray<TransformComponent> &transforms = registry.get_components<TransformComponent>();
        SparseArray<BoxColliderComponent> &colliders =
            registry.get_components<BoxColliderComponent>();

        for (size_t index1 = 0; index1 < colliders.size(); index1 += 1) {
            if (colliders[index1] == std::nullopt || transforms[index1] == std::nullopt)
                continue;
            for (size_t index2 = 0; index2 < colliders.size(); index2 += 1) {
                if (colliders[index2] == std::nullopt || transforms[index2] == std::nullopt ||
                    index1 == index2)
                    continue;
                if (transforms[index1]->position_x < transforms[index2]->position_x +
                            (colliders[index2]->width * transforms[index2]->scale_x) &&
                    transforms[index1]->position_x +
                            (colliders[index1]->width * transforms[index1]->scale_x) >
                        transforms[index2]->position_x &&
                    transforms[index1]->position_y < transforms[index2]->position_y +
                            (colliders[index2]->height * transforms[index2]->scale_y) &&
                    transforms[index1]->position_y +
                            (colliders[index1]->height * transforms[index1]->scale_y) >
                        transforms[index2]->position_y)
                    DEBUG(("Collision\n"));
            }
        }
    }
} // namespace rtype
