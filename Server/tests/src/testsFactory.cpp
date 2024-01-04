/*
** EPITECH PROJECT, 2023
** src
** File description:
** testsFactory
*/

#include <gtest/gtest.h>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/dlloader/DlLoader.hpp>

TEST(ServerEntityFactory, constructor_with_exception)
{
    dl::DlLoader<rtype::ECSManager> ecs{};

    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    EXPECT_THROW(rserver::ServerEntityFactory::create("unknown type", ecs.get_class()),
                 rserver::ServerEntityFactory::FactoryException);
}

TEST(ServerEntityFactory, constructor_without_register)
{
    dl::DlLoader<rtype::ECSManager> ecs{};

    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    EXPECT_THROW(rserver::ServerEntityFactory::create("BasicEnemy", ecs.get_class()),
                 rtype::ECSManager::ECSException);
    EXPECT_THROW(rserver::ServerEntityFactory::create("Player", ecs.get_class()),
                 rtype::ECSManager::ECSException);
    EXPECT_THROW(rserver::ServerEntityFactory::create("OtherPlayer", ecs.get_class()),
                 rtype::ECSManager::ECSException);
    EXPECT_THROW(rserver::ServerEntityFactory::create("Bullet", ecs.get_class()),
                 rtype::ECSManager::ECSException);
}

TEST(ServerEntityFactory, constructor_no_throw)
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
    EXPECT_NO_THROW(rserver::ServerEntityFactory::create("BasicEnemy", ecs.get_class()));
    EXPECT_NO_THROW(rserver::ServerEntityFactory::create("Player", ecs.get_class()));
    EXPECT_NO_THROW(rserver::ServerEntityFactory::create("OtherPlayer", ecs.get_class()));
    EXPECT_NO_THROW(rserver::ServerEntityFactory::create("Bullet", ecs.get_class()));
}
