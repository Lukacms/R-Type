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

size_t rserver::ServerEntityFactory::create(const std::string &type, rtype::ECSManager &ecs_manager)
{
    if (type == "Enemy") {
        return create_enemy(ecs_manager);
    }
    if (type == "Player") {
        return create_player(ecs_manager);
    }
    if (type == "OtherPlayer") {
        return create_other_player(ecs_manager);
    }
    if (type == "Bullet") {
        return create_bullet(ecs_manager);
    }
    throw std::runtime_error("Unknown entity type");
}

size_t rserver::ServerEntityFactory::create_enemy(rtype::ECSManager &ecs_manager)
{
    size_t entity = ecs_manager.create_entity();
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    collider.insert_at(entity, rtype::BoxColliderComponent{50, 50});
    tag.insert_at(entity, rtype::TagComponent{"BasicEnemy"});
    transform.insert_at(entity, rtype::TransformComponent{});
    return entity;
}

size_t rserver::ServerEntityFactory::create_player(rtype::ECSManager &ecs_manager)
{
    size_t entity = ecs_manager.create_entity();
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    collider.insert_at(entity, rtype::BoxColliderComponent{50, 50});
    tag.insert_at(entity, rtype::TagComponent{"Player"});
    transform.insert_at(entity, rtype::TransformComponent{300, 400, 0, 0, 0, 0});
    return entity;
}

size_t rserver::ServerEntityFactory::create_other_player(rtype::ECSManager &ecs_manager)
{
    size_t entity = ecs_manager.create_entity();
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    collider.insert_at(entity, rtype::BoxColliderComponent{50, 50});
    tag.insert_at(entity, rtype::TagComponent{"OtherPlayer"});
    transform.insert_at(entity, rtype::TransformComponent{});
    return entity;
}

size_t rserver::ServerEntityFactory::create_bullet(rtype::ECSManager &ecs_manager)
{
    size_t entity = ecs_manager.create_entity();
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    health.insert_at(entity, rtype::HealthComponent{0, 0});
    collider.insert_at(entity, rtype::BoxColliderComponent{10, 10});
    tag.insert_at(entity, rtype::TagComponent{"Bullet"});
    transform.insert_at(entity, rtype::TransformComponent{});
    transform[entity]->velocity_x = 10;
    return entity;
}
