//
// Created by kane on 14/01/24.
//

#include <gtest/gtest.h>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/ClockComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Factory/ClientEntityFactory.hh>
#include <rtype/dlloader/DlLoader.hpp>

TEST(ClientEntityFactory, construction_of_unknown_entity)
{
    dl::DlLoader<rtype::ECSManager> ecs{};
    rtype::SparseArray<rtype::BoxColliderComponent> boxes{};
    rtype::SparseArray<rtype::TransformComponent> transform{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::HealthComponent> healths{};
    rtype::SparseArray<rtype::ClockComponent> clocks{};
    rtype::SparseArray<rtype::SpriteComponent> sprites{};
    rtype::SparseArray<rtype::AnimationComponent> animations{};

    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    ecs.get_class().register_component(transform);
    ecs.get_class().register_component(boxes);
    ecs.get_class().register_component(tags);
    ecs.get_class().register_component(healths);
    ecs.get_class().register_component(clocks);
    ecs.get_class().register_component(animations);
    ecs.get_class().register_component(sprites);
    EXPECT_THROW(rclient::ClientEntityFactory::create(100, "unknown type", ecs.get_class()),
                 rclient::ClientEntityFactory::FactoryException);
}

TEST(ClientEntityFactory, construction_with_not_enough_sparse_array)
{
    dl::DlLoader<rtype::ECSManager> ecs{};
    rtype::SparseArray<rtype::BoxColliderComponent> boxes{};
    rtype::SparseArray<rtype::TransformComponent> transform{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::HealthComponent> healths{};

    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    ecs.get_class().register_component(transform);
    ecs.get_class().register_component(boxes);
    ecs.get_class().register_component(tags);
    ecs.get_class().register_component(healths);
    EXPECT_THROW(rclient::ClientEntityFactory::create(100, "Player", ecs.get_class()),
                 rtype::ECSManager::ECSException);
}

TEST(ClientEntityFactory, construction_with_already_allocate_entity)
{
    dl::DlLoader<rtype::ECSManager> ecs{};
    rtype::SparseArray<rtype::BoxColliderComponent> boxes{};
    rtype::SparseArray<rtype::TransformComponent> transform{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::HealthComponent> healths{};
    rtype::SparseArray<rtype::ClockComponent> clocks{};
    rtype::SparseArray<rtype::SpriteComponent> sprites{};
    rtype::SparseArray<rtype::AnimationComponent> animations{};
    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");

    ecs.get_class().register_component(transform);
    ecs.get_class().register_component(boxes);
    ecs.get_class().register_component(tags);
    ecs.get_class().register_component(healths);
    ecs.get_class().register_component(clocks);
    ecs.get_class().register_component(animations);
    ecs.get_class().register_component(sprites);
    ecs.get_class().create_entity(100);
    EXPECT_THROW(rclient::ClientEntityFactory::create(100, "BasicEnemy", ecs.get_class()),
                 rtype::ECSManager::ECSException);
}

TEST(ClientEntityFactory, construction_successful)
{
    dl::DlLoader<rtype::ECSManager> ecs{};
    rtype::SparseArray<rtype::BoxColliderComponent> boxes{};
    rtype::SparseArray<rtype::TransformComponent> transform{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::HealthComponent> healths{};
    rtype::SparseArray<rtype::ClockComponent> clocks{};
    rtype::SparseArray<rtype::SpriteComponent> sprites{};
    rtype::SparseArray<rtype::AnimationComponent> animations{};
    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");

    ecs.get_class().register_component(transform);
    ecs.get_class().register_component(boxes);
    ecs.get_class().register_component(tags);
    ecs.get_class().register_component(healths);
    ecs.get_class().register_component(clocks);
    ecs.get_class().register_component(animations);
    ecs.get_class().register_component(sprites);
    EXPECT_NO_THROW(rclient::ClientEntityFactory::create(0, "BasicEnemy", ecs.get_class()));
    EXPECT_NO_THROW(rclient::ClientEntityFactory::create(1, "Player", ecs.get_class()));
    EXPECT_NO_THROW(rclient::ClientEntityFactory::create(2, "PlayerBullet", ecs.get_class()));
    auto &t = ecs.get_class().get_components<rtype::TagComponent>();
    EXPECT_STREQ(t[0]->tag.c_str(), "BasicEnemy");
    EXPECT_STREQ(t[1]->tag.c_str(), "Player");
    EXPECT_STREQ(t[2]->tag.c_str(), "PlayerBullet");
}
