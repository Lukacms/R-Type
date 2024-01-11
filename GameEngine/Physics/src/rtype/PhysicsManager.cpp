/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** PhysicsManager
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/PhysicsManager.hh>

void rtype::PhysicsManager::check_collisions(ECSManager &ecs_manager)
{
    SparseArray<TransformComponent> &transforms = ecs_manager.get_components<TransformComponent>();
    SparseArray<BoxColliderComponent> &colliders =
        ecs_manager.get_components<BoxColliderComponent>();
    Collision collision{};

    m_collisions.clear();
    for (size_t entity1 = 0; entity1 < colliders.size(); entity1 += 1) {
        collision.entity = entity1;
        collision.collided.clear();
        if (!colliders[entity1].has_value() || !transforms[entity1].has_value())
            continue;
        for (size_t entity2 = 0; entity2 < colliders.size(); entity2 += 1) {
            if (!colliders[entity2].has_value() || !transforms[entity2].has_value() ||
                entity1 == entity2)
                continue;
            if (transforms[entity1]->position_x < transforms[entity2]->position_x +
                        (colliders[entity2]->width * std::abs(transforms[entity2]->scale_x)) &&
                transforms[entity1]->position_x +
                        (colliders[entity1]->width * std::abs(transforms[entity1]->scale_x)) >
                    transforms[entity2]->position_x &&
                transforms[entity1]->position_y < transforms[entity2]->position_y +
                        (colliders[entity2]->height * std::abs(transforms[entity2]->scale_y)) &&
                transforms[entity1]->position_y +
                        (colliders[entity1]->height * std::abs(transforms[entity1]->scale_y)) >
                    transforms[entity2]->position_y)
                collision.collided.emplace_back(entity2);
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
    throw PhysicsException();
}

bool rtype::PhysicsManager::is_collided(std::size_t entity1, std::size_t entity2) const
{
    Collision collisions{};

    for (const auto &collision : m_collisions) {
        if (collision.entity == entity1)
            collisions = collision;
    }
    return std::any_of(collisions.collided.cbegin(), collisions.collided.cend(),
                       [entity2](std::size_t entity) { return entity2 == entity; });
}

/* Exception */
const char *rtype::PhysicsManager::PhysicsException::what() const noexcept
{
    return EXCEPTION_OCCURED.data();
}
