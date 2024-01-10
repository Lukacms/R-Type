/*
** EPITECH PROJECT, 2023
** game
** File description:
** ServerEntityFactory
*/

#include <fstream>
#include <rtype.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/ClockComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Factory/ServerEntityFactory.hh>

size_t rserver::ServerEntityFactory::create(const std::string &type, rtype::ECSManager &ecs_manager)
{
    if (type == "BasicEnemy") {
        return create_enemy(ecs_manager);
    }
    if (type == "KamikazeEnemy") {
        return create_kamikaze_enemy(ecs_manager);
    }
    if (type == "SnakeEnemy") {
        return create_snake_enemy(ecs_manager);
    }
    if (type == "Player") {
        return create_player(ecs_manager);
    }
    if (type == "Bullet") {
        return create_bullet(ecs_manager);
    }
    if (type == "Upgrade") {
        return create_upgrade(ecs_manager);
    }
    throw FactoryException("Unknown entity type");
}

size_t rserver::ServerEntityFactory::create_json(const std::string &type,
                                                 rtype::ECSManager &ecs_manager)
{
    std::ifstream file{ENTITIES_PATH.data()};
    njson entities{};
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &clocks{ecs_manager.get_components<rtype::ClockComponent>()};

    if (!file.is_open())
        throw FactoryException("Couldn't find entities infos");
    entities = njson::parse(file);
    try {
        for (auto &entity : entities["entities"]) {
            if (entity["tag"] != type)
                continue;
            size_t e_id{ecs_manager.create_entity()};
            tag.insert_at(e_id, rtype::TagComponent{type});
            if (!entity["clock"].is_null() && entity["clock"] == true)
                clocks.insert_at(e_id, {});
            if (!entity["collider"].is_null())
                collider.insert_at(e_id, entity["collider"]);
            if (!entity["transform"].is_null())
                transform.insert_at(e_id, entity["transform"]);
            if (!entity["health"].is_null())
                health.insert_at(e_id, entity["health"]);
            return e_id;
        }
    } catch (nlohmann::json::exception &e) {
        DEBUG(("%s%s", e.what(), ENDL));
    }
    throw FactoryException("Unknown entity type");
}

size_t rserver::ServerEntityFactory::create_enemy(rtype::ECSManager &ecs_manager)
{
    size_t entity{ecs_manager.create_entity()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    health.insert_at(entity, BASIC_HEALTH);
    collider.insert_at(entity, BASIC_COLLIDER);
    tag.insert_at(entity, rtype::TagComponent{"BasicEnemy"});
    transform.insert_at(entity, TRANS_ENEMY);
    return entity;
}

size_t rserver::ServerEntityFactory::create_player(rtype::ECSManager &ecs_manager)
{
    size_t entity{ecs_manager.create_entity()};
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    health.insert_at(entity, BASIC_HEALTH);
    collider.insert_at(entity, BASIC_COLLIDER);
    tag.insert_at(entity, rtype::TagComponent{"Player"});
    transform.insert_at(entity, TRANS_PLAYER);
    return entity;
}

size_t rserver::ServerEntityFactory::create_kamikaze_enemy(rtype::ECSManager &ecs_manager)
{
    size_t entity{ecs_manager.create_entity()};
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &clocks{ecs_manager.get_components<rtype::ClockComponent>()};

    health.insert_at(entity, BASIC_HEALTH);
    collider.insert_at(entity, KAMIKAZE_COLLIDER);
    tag.insert_at(entity, rtype::TagComponent{"KamikazeEnemy"});
    transform.insert_at(entity, TRANS_ENEMY);
    clocks.insert_at(entity, {});
    return entity;
}

size_t rserver::ServerEntityFactory::create_bullet(rtype::ECSManager &ecs_manager)
{
    size_t entity{ecs_manager.create_entity()};
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    health.insert_at(entity, rtype::HealthComponent{0, 0});
    collider.insert_at(entity, COLLIDER_BULLET);
    tag.insert_at(entity, rtype::TagComponent{"Bullet"});
    transform.insert_at(entity, TRANS_BULLET);
    transform[entity]->velocity_x = 1;
    return entity;
}

size_t rserver::ServerEntityFactory::create_upgrade(rtype::ECSManager &ecs_manager)
{
    size_t entity = ecs_manager.create_entity();
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    collider.insert_at(entity, rtype::BoxColliderComponent{36, 36});
    tag.insert_at(entity, rtype::TagComponent{"Upgrade"});
    transform.insert_at(entity, rtype::TransformComponent{0, 0, 0, 0, 1, 1});
    transform[entity]->velocity_x = -5;
    return entity;
}

size_t rserver::ServerEntityFactory::create_snake_enemy(rtype::ECSManager &ecs_manager)
{
    size_t entity{ecs_manager.create_entity()};
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &clocks{ecs_manager.get_components<rtype::ClockComponent>()};

    health.insert_at(entity, BASIC_HEALTH);
    collider.insert_at(entity, {32, 32});
    tag.insert_at(entity, rtype::TagComponent{"SnakeEnemy"});
    transform.insert_at(entity, TRANS_ENEMY);
    clocks.insert_at(entity, {});
    return entity;
}

/* exception */
rserver::ServerEntityFactory::FactoryException::FactoryException(std::string &&perror_msg)
    : error_msg{std::move(perror_msg)}
{
}

const char *rserver::ServerEntityFactory::FactoryException::what() const noexcept
{
    return this->error_msg.c_str();
}
