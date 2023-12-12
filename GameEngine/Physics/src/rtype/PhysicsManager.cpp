//
// Created by kane on 12/12/23.
//

#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/PhysicsManager.hh>

void rtype::PhysicsManager::check_collisions(ComponentManager &component_manager)
{
    SparseArray<TransformComponent> &transforms =
        component_manager.get_components<TransformComponent>();
    SparseArray<BoxColliderComponent> &colliders =
        component_manager.get_components<BoxColliderComponent>();
    Collision collision{};

    m_collisions.clear();
    for (size_t index1 = 0; index1 < colliders.size(); index1 += 1) {
        collision.entity = index1;
        collision.collided.clear();
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
                collision.collided.emplace_back(index2);
        }
        m_collisions.emplace_back(collision);
    }
}

std::vector<std::size_t> rtype::PhysicsManager::get_collision(std::size_t entity) const
{
    for (const auto &collision : m_collisions) {
        if (collision.entity == entity)
            return collision.collided;
    }
}

bool rtype::PhysicsManager::is_collided(std::size_t entity1, std::size_t entity2) const
{
    Collision collisions{};

    for (const auto &collision : m_collisions) {
        if (collision.entity == entity1)
            collisions = collision;
    }
    return std::find(collisions.collided.begin(), collisions.collided.end(), entity2) ==
        std::end(collisions.collided);
}
