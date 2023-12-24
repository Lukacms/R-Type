//
// Created by kane on 12/12/23.
//

#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/PhysicsManager.hh>

void rtype::PhysicsManager::check_collisions(ECSManager &ecs_manager)
{
    SparseArray<TransformComponent> &transforms =
        ecs_manager.get_components<TransformComponent>();
    SparseArray<BoxColliderComponent> &colliders =
        ecs_manager.get_components<BoxColliderComponent>();
    Collision collision{};

    m_collisions.clear();
    for (size_t entity1 = 0; entity1 < colliders.size(); entity1 += 1) {
        collision.entity = entity1;
        collision.collided.clear();
        if (colliders[entity1] == std::nullopt || transforms[entity1] == std::nullopt)
            continue;
        for (size_t entity2 = 0; entity2 < colliders.size(); entity2 += 1) {
            if (colliders[entity2] == std::nullopt || transforms[entity2] == std::nullopt ||
                entity1 == entity2)
                continue;
            if (transforms[entity1]->position_x < transforms[entity2]->position_x +
                        (colliders[entity2]->width * transforms[entity2]->scale_x) &&
                transforms[entity1]->position_x +
                        (colliders[entity1]->width * transforms[entity1]->scale_x) >
                    transforms[entity2]->position_x &&
                transforms[entity1]->position_y < transforms[entity2]->position_y +
                        (colliders[entity2]->height * transforms[entity2]->scale_y) &&
                transforms[entity1]->position_y +
                        (colliders[entity1]->height * transforms[entity1]->scale_y) >
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
    return std::find(collisions.collided.begin(), collisions.collided.end(), entity2) ==
        std::end(collisions.collided);
}

/* Exception */
const char *rtype::PhysicsManager::PhysicsException::what() const noexcept
{
    return EXCEPTION_OCCURED.data();
}
