//
// Created by kane on 14/01/24.
//

#include <gtest/gtest.h>
#include <optional>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/PhysicsManager.hh>

TEST(PhysicsManager, get_collisions)
{
    rtype::ECSManager manager{};
    rtype::PhysicsManager physics{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    rtype::SparseArray<rtype::BoxColliderComponent> colliders{};

    manager.register_component(transforms);
    manager.register_component(colliders);
    manager.create_entity(0);
    manager.create_entity(50);
    auto &t = manager.get_components<rtype::TransformComponent>();
    auto &c = manager.get_components<rtype::BoxColliderComponent>();
    t.insert_at(0, {0, 0, 1, 1, 1, 1});
    c.insert_at(0, {50, 50});
    t.insert_at(50, {20, 20, 1, 1, 1, 1});
    c.insert_at(50, {20, 20});
    physics.check_collisions(manager);
    EXPECT_TRUE(physics.is_collided(0, 50));
    c[0]->height = 10;
    c[0]->width = 10;
    physics.check_collisions(manager);
    EXPECT_FALSE(physics.is_collided(0, 50));
}

TEST(PhysicsManager, get_list_collision)
{

    rtype::ECSManager manager{};
    rtype::PhysicsManager physics{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    rtype::SparseArray<rtype::BoxColliderComponent> colliders{};

    manager.register_component(transforms);
    manager.register_component(colliders);
    manager.create_entity(0);
    manager.create_entity(50);
    manager.create_entity(100);
    auto &t = manager.get_components<rtype::TransformComponent>();
    auto &c = manager.get_components<rtype::BoxColliderComponent>();
    t.insert_at(0, {0, 0, 1, 1, 1, 1});
    c.insert_at(0, {50, 50});
    t.insert_at(50, {20, 20, 1, 1, 1, 1});
    c.insert_at(50, {20, 20});
    t.insert_at(100, {20, 20, 1, 1, 1, 1});
    c.insert_at(100, {20, 20});
    physics.check_collisions(manager);
    EXPECT_EQ(physics.get_collision(0), (std::vector<std::size_t>{50, 100}));
    t[100]->position_x = 60;
    t[100]->position_y = 60;
    physics.check_collisions(manager);
    EXPECT_EQ(physics.get_collision(0), (std::vector<std::size_t>{50}));
}

TEST(PhysicsManager, entity_does_not_exist)
{
    rtype::ECSManager manager{};
    rtype::PhysicsManager physics{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    rtype::SparseArray<rtype::BoxColliderComponent> colliders{};

    manager.register_component(transforms);
    manager.register_component(colliders);
    manager.create_entity(0);
    manager.create_entity(50);
    auto &t = manager.get_components<rtype::TransformComponent>();
    auto &c = manager.get_components<rtype::BoxColliderComponent>();
    t.insert_at(0, {0, 0, 1, 1, 1, 1});
    c.insert_at(0, {50, 50});
    t.insert_at(50, {20, 20, 1, 1, 1, 1});
    c.insert_at(50, {20, 20});
    physics.check_collisions(manager);
    EXPECT_FALSE(physics.is_collided(2, 50));
    EXPECT_FALSE(physics.is_collided(50, 2));
    EXPECT_THROW(physics.get_collision(2), rtype::PhysicsManager::PhysicsException);
}
