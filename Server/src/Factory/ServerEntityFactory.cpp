/*
** EPITECH PROJECT, 2023
** game
** File description:
** ServerEntityFactory
*/

#include "rtype/Factory/ServerEntityFactory.hh"
#include "rtype/Components/BoxColliderComponent.hh"
#include "rtype/Components/HealthComponent.hh"
#include "rtype/Components/TagComponent.hh"
#include "rtype/Components/TransformComponent.hh"

size_t ServerEntityFactory::create(const std::string &type, rtype::ECSManager &ecsManager)
{
    if (type == "Enemy") {
        return create_enemy(ecsManager);
    } else if (type == "Player") {
        return create_player(ecsManager);
    } else if (type == "OtherPlayer") {
        return create_other_player(ecsManager);
    } else if (type == "Bullet") {
        return create_bullet(ecsManager);
    } else {
        throw std::runtime_error("Unknown entity type");
    }
}

size_t ServerEntityFactory::create_enemy(rtype::ECSManager &ecsManager)
{
    size_t entity = ecsManager.create_entity();
    auto &health{ecsManager.get_components<rtype::HealthComponent>()};
    health.insert_at(entity, rtype::HealthComponent{100, 100});
    auto &transform{ecsManager.get_components<rtype::TransformComponent>()};
    transform.insert_at(entity, rtype::TransformComponent{});
    auto &collider{ecsManager.get_components<rtype::BoxColliderComponent>()};
    collider.insert_at(entity, rtype::BoxColliderComponent{50, 50});
    auto &tag{ecsManager.get_components<rtype::TagComponent>()};
    tag.insert_at(entity, rtype::TagComponent{"BasicEnemy"});
    return entity;
}

size_t ServerEntityFactory::create_player(rtype::ECSManager &ecsManager)
{
    size_t entity = ecsManager.create_entity();
    auto &health{ecsManager.get_components<rtype::HealthComponent>()};
    health.insert_at(entity, rtype::HealthComponent{100, 100});
    auto &transform{ecsManager.get_components<rtype::TransformComponent>()};
    transform.insert_at(entity, rtype::TransformComponent{});
    auto &collider{ecsManager.get_components<rtype::BoxColliderComponent>()};
    collider.insert_at(entity, rtype::BoxColliderComponent{50, 50});
    auto &tag{ecsManager.get_components<rtype::TagComponent>()};
    tag.insert_at(entity, rtype::TagComponent{"Player"});
    return entity;
}

size_t ServerEntityFactory::create_other_player(rtype::ECSManager &ecsManager)
{
    size_t entity = ecsManager.create_entity();
    auto &health{ecsManager.get_components<rtype::HealthComponent>()};
    health.insert_at(entity, rtype::HealthComponent{100, 100});
    auto &transform{ecsManager.get_components<rtype::TransformComponent>()};
    transform.insert_at(entity, rtype::TransformComponent{});
    auto &collider{ecsManager.get_components<rtype::BoxColliderComponent>()};
    collider.insert_at(entity, rtype::BoxColliderComponent{50, 50});
    auto &tag{ecsManager.get_components<rtype::TagComponent>()};
    tag.insert_at(entity, rtype::TagComponent{"OtherPlayer"});
    return entity;
}

size_t ServerEntityFactory::create_bullet(rtype::ECSManager &ecsManager)
{
    size_t entity = ecsManager.create_entity();
    auto &health{ecsManager.get_components<rtype::HealthComponent>()};
    health.insert_at(entity, rtype::HealthComponent{0, 0});
    auto &transform{ecsManager.get_components<rtype::TransformComponent>()};
    transform.insert_at(entity, rtype::TransformComponent{});
    auto &collider{ecsManager.get_components<rtype::BoxColliderComponent>()};
    collider.insert_at(entity, rtype::BoxColliderComponent{10, 10});
    auto &tag{ecsManager.get_components<rtype::TagComponent>()};
    tag.insert_at(entity, rtype::TagComponent{"Bullet"});
    return entity;
}
