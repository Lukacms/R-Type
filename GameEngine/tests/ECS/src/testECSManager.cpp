//
// Created by kane on 14/01/24.
//

#include <gtest/gtest.h>
#include <optional>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>

TEST(ECSManager, create_new_entity)
{
    rtype::ECSManager manager{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};

    manager.register_component(transforms);
    manager.create_entity();
    EXPECT_EQ(manager.get_used_entity(), std::vector<std::size_t>{0});
    auto &t = manager.get_components<rtype::TransformComponent>();
    t.insert_at(0, {1, 1, 1, 1, 1, 1});
    EXPECT_TRUE(t[0].has_value());
    t[0]->position_x = 1000;
    EXPECT_EQ(manager.get_component<rtype::TransformComponent>(0).position_x, 1000);
}

TEST(ECSManager, destroy_entity)
{
    rtype::ECSManager manager{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};

    manager.register_component(transforms);
    manager.create_entity();
    auto &t = manager.get_components<rtype::TransformComponent>();
    t.insert_at(0, {1, 1, 1, 1, 1, 1});
    t[0]->position_x = 1000;
    manager.delete_entity(0);
    EXPECT_EQ(manager.get_used_entity().size(), 0);
    EXPECT_FALSE(t[0].has_value());
}

TEST(ECSManager, remove_component)
{
    rtype::ECSManager manager{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};

    manager.register_component(transforms);
    manager.create_entity(0);
    auto &t = manager.get_components<rtype::TransformComponent>();
    t.insert_at(0, {1, 1, 1, 1, 1, 1});
    manager.remove_component<rtype::TransformComponent>(0);
    EXPECT_FALSE(t[0].has_value());
}

TEST(ECSManager, create_defined_entity)
{
    rtype::ECSManager manager{};

    manager.create_entity(255);
    EXPECT_TRUE(manager.is_entity_used(255));
}

TEST(ECSManager, apply_systems)
{
    rtype::ECSManager manager{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    std::function<void(rtype::ComponentManager &, float)> transform_system{
        &rtype::transform_system};

    manager.register_component(transforms);
    manager.create_entity(0);
    manager.add_system(transform_system);
    auto &t = manager.get_components<rtype::TransformComponent>();
    t.insert_at(0, {1, 1, 1, 1, 1, 1});
    manager.apply_system(1);
    EXPECT_EQ(t[0]->position_x, 2);
}

TEST(ECSManager, no_existing_sparse_array)
{
    rtype::ECSManager manager{};

    EXPECT_THROW(manager.get_components<rtype::TransformComponent>(),
                 rtype::ECSManager::ECSException);
}

TEST(ECSManager, create_entity_already_existing)
{
    rtype::ECSManager manager{};

    manager.create_entity(0);
    EXPECT_THROW(manager.create_entity(0), rtype::ECSManager::ECSException);
}

TEST(ECSManager, create_too_high_entity)
{
    rtype::ECSManager manager{};

    EXPECT_THROW(manager.create_entity(10001);, rtype::ECSManager::ECSException);
}
