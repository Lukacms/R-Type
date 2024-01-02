//
// Created by kane on 11/12/23.
//

#include <iostream>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>

namespace rtype
{
    void collider_system(ComponentManager &reg, [[maybe_unused]] float delta_time)
    {
        SparseArray<TransformComponent> &trans = reg.get_components<TransformComponent>();
        SparseArray<BoxColliderComponent> &coll = reg.get_components<BoxColliderComponent>();

        for (size_t ind1 = 0; ind1 < coll.size(); ind1 += 1) {
            if (coll[ind1] == std::nullopt || trans[ind1] == std::nullopt)
                continue;
            for (size_t ind2 = 0; ind2 < coll.size(); ind2 += 1) {
                if (coll[ind2] == std::nullopt || trans[ind2] == std::nullopt || ind1 == ind2)
                    continue;
                if (trans[ind1]->position_x <
                        trans[ind2]->position_x + (coll[ind2]->width * trans[ind2]->scale_x) &&
                    trans[ind1]->position_x + (coll[ind1]->width * trans[ind1]->scale_x) >
                        trans[ind2]->position_x &&
                    trans[ind1]->position_y <
                        trans[ind2]->position_y + (coll[ind2]->height * trans[ind2]->scale_y) &&
                    trans[ind1]->position_y + (coll[ind1]->height * trans[ind1]->scale_y) >
                        trans[ind2]->position_y) {
                    DEBUG(("Collision\n"));
                }
            }
        }
    }
} // namespace rtype
