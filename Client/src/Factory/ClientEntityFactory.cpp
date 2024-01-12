/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** factory source file
*/

#include <fstream>
#include <iostream>
#include <rtype.hh>
#include <rtype/Components/AnimationComponent.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Factory/ClientEntityFactory.hh>

size_t rclient::ClientEntityFactory::create(std::size_t entity, const std::string &type,
                                            rtype::ECSManager &ecs_manager)
{
    try {
        return create_json(entity, type, ecs_manager);
    } catch (FactoryException &e) {
        throw e;
    } catch (rtype::ECSManager::ECSException &e) {
        throw e;
    }
}

size_t rclient::ClientEntityFactory::create_json(std::size_t entity, const std::string &type,
                                                 rtype::ECSManager &ecs_manager)
{
    std::ifstream file{ENTITIES_PATH.data()};
    njson entities{};
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &animations{ecs_manager.get_components<rtype::AnimationComponent>()};
    std::size_t new_entity = ecs_manager.create_entity(entity);

    if (!file.is_open())
        throw FactoryException("Couldn't find entities infos");
    entities = njson::parse(file);
    try {
        for (auto &ejson : entities["entities"]) {
            if (ejson["tag"] != type)
                continue;
            tag.insert_at(new_entity, rtype::TagComponent{type});
            if (!ejson["collider"].is_null())
                collider.insert_at(new_entity, ejson["collider"]);
            if (!ejson["health"].is_null())
                health.insert_at(new_entity, ejson["health"]);
            if (!ejson["transform"].is_null())
                transform.insert_at(new_entity, ejson["transform"]);
            if (!ejson["sprite"].is_null())
                sprite.insert_at(new_entity, ejson["sprite"]);
            if (!ejson["animation"].is_null())
                animations.insert_at(new_entity, ejson["animation"]);
            return new_entity;
        }
    } catch (nlohmann::json::exception &e) {
        DEBUG(("%s%s", e.what(), ENDL));
    }
    throw FactoryException("Unknown entity type");
}

size_t rclient::ClientEntityFactory::create_enemy(std::size_t entity,
                                                  rtype::ECSManager &ecs_manager)
{
    try {
        auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
        auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
        auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
        auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};

        health.insert_at(entity, BASIC_HEALTH);
        transform.insert_at(entity, rtype::TransformComponent{});
        tag.insert_at(entity, rtype::TagComponent{"BasicEnemy"});
        sprite.insert_at(entity, rtype::SpriteComponent{});
        sprite[entity]->texture_path = "./assets/entities/BasicEnemy.png";
        sprite[entity]->rectangle = TEXTURERECT_SHIP;
        sprite[entity]->origin = {ORIGIN_ENEMY.x, ORIGIN_ENEMY.y};
        transform[entity]->scale_x = -2;
        transform[entity]->scale_y = 2;
        return entity;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

size_t rclient::ClientEntityFactory::create_player(std::size_t entity,
                                                   rtype::ECSManager &ecs_manager)
{
    try {
        auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
        auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
        auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
        auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
        auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};

        health.insert_at(entity, BASIC_HEALTH);
        transform.insert_at(entity, rtype::TransformComponent{});
        tag.insert_at(entity, rtype::TagComponent{"Player"});
        sprite.insert_at(entity, rtype::SpriteComponent{});
        sprite[entity]->texture_path = "./assets/entities/Spaceship.png";
        sprite[entity]->rectangle = TEXTURERECT_SHIP;
        transform[entity]->scale_x = 2;
        transform[entity]->scale_y = 2;
        collider.insert_at(entity, BASIC_COLLIDER);
        return entity;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

size_t rclient::ClientEntityFactory::create_kamikaze_enemy(std::size_t entity,
                                                           rtype::ECSManager &ecs_manager)
{
    try {
        auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
        auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
        auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
        auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
        auto &animations{ecs_manager.get_components<rtype::AnimationComponent>()};

        health.insert_at(entity, BASIC_HEALTH);
        transform.insert_at(entity, rtype::TransformComponent{});
        tag.insert_at(entity, rtype::TagComponent{"KamikazeEnemy"});
        sprite.insert_at(entity, rtype::SpriteComponent{});
        animations.insert_at(entity, rtype::AnimationComponent{});
        sprite[entity]->texture_path = "./assets/entities/KamikazeEnemy.png";
        sprite[entity]->rectangle = {0, 0, 18, 18};
        sprite[entity]->origin = {0, 0};
        transform[entity]->scale_x = 2;
        transform[entity]->scale_y = 2;
        animations[entity]->current_animation = "Idle";
        animations[entity]->animation_clips.push_back({"Idle",
                                                       true,
                                                       20,
                                                       {{0, 0, 18, 18},
                                                        {18, 0, 18, 18},
                                                        {18 * 2, 0, 18, 18},
                                                        {18 * 3, 0, 18, 18},
                                                        {18 * 4, 0, 18, 18},
                                                        {18 * 5, 0, 18, 18},
                                                        {18 * 6, 0, 18, 18},
                                                        {18 * 7, 0, 18, 18},
                                                        {18 * 8, 0, 18, 18},
                                                        {18 * 9, 0, 18, 18}}});
        DEBUG(("SUCCESS\n"));
        return entity;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

size_t rclient::ClientEntityFactory::create_bullet(std::size_t entity,
                                                   rtype::ECSManager &ecs_manager)
{
    try {
        auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
        auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
        auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
        auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};

        transform.insert_at(entity, rtype::TransformComponent{});
        tag.insert_at(entity, rtype::TagComponent{"PlayerBullet"});
        sprite.insert_at(entity, rtype::SpriteComponent{});
        sprite[entity]->texture_path = "./assets/entities/PlayerShoot.png";
        transform[entity]->scale_x = 2;
        transform[entity]->scale_y = 2;
        sprite[entity]->rectangle = {0, 0, 31, 6};
        collider.insert_at(entity, BASIC_COLLIDER);
        return entity;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

size_t rclient::ClientEntityFactory::create_upgrade(std::size_t entity,
                                                    rtype::ECSManager &ecs_manager)
{
    try {
        auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
        auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
        auto &sprites{ecs_manager.get_components<rtype::SpriteComponent>()};
        auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
        auto &animations{ecs_manager.get_components<rtype::AnimationComponent>()};

        collider.insert_at(entity, rtype::BoxColliderComponent{});
        tag.insert_at(entity, rtype::TagComponent{"Upgrade"});
        transform.insert_at(entity, rtype::TransformComponent{});
        sprites.insert_at(entity, rtype::SpriteComponent{});
        animations.insert_at(entity, rtype::AnimationComponent{});
        sprites[entity]->texture_path = "./Client/assets/Upgrade.png";
        transform[entity]->scale_x = 2;
        transform[entity]->scale_y = 2;
        sprites[entity]->rectangle = {0, 0, 17, 17};
        animations[entity]->current_animation = "Idle";
        animations[entity]->animation_clips.push_back({"Idle",
                                                       true,
                                                       50,
                                                       {{0, 0, 17, 17},
                                                        {17, 0, 17, 17},
                                                        {34, 0, 17, 17},
                                                        {51, 0, 17, 17},
                                                        {68, 0, 17, 17},
                                                        {85, 0, 17, 17},
                                                        {102, 0, 17, 17},
                                                        {119, 0, 17, 17},
                                                        {136, 0, 17, 17},
                                                        {153, 0, 17, 17},
                                                        {170, 0, 17, 17},
                                                        {187, 0, 17, 17}}});
        return entity;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

size_t rclient::ClientEntityFactory::create_UFO_enemy(std::size_t entity,
                                                      rtype::ECSManager &ecs_manager)
{
    try {
        auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
        auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
        auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
        auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
        auto &animations{ecs_manager.get_components<rtype::AnimationComponent>()};

        health.insert_at(entity, BASIC_HEALTH);
        transform.insert_at(entity, rtype::TransformComponent{});
        tag.insert_at(entity, rtype::TagComponent{"SnakeEnemy"});
        sprite.insert_at(entity, rtype::SpriteComponent{});
        animations.insert_at(entity, rtype::AnimationComponent{});
        sprite[entity]->texture_path = "./assets/entities/UFOEnemy.png";
        sprite[entity]->rectangle = {0, 0, 32, 32};
        sprite[entity]->origin = {0, 0};
        transform[entity]->scale_x = 2;
        transform[entity]->scale_y = 2;
        animations[entity]->current_animation = "Idle";
        animations[entity]->animation_clips.push_back({"Idle",
                                                       true,
                                                       20,
                                                       {{0, 0, 32, 32},
                                                        {32, 0, 32, 32},
                                                        {32 * 2, 0, 32, 32},
                                                        {32 * 3, 0, 32, 32},
                                                        {32 * 4, 0, 32, 32},
                                                        {32 * 5, 0, 32, 32},
                                                        {32 * 6, 0, 32, 32},
                                                        {32 * 7, 0, 32, 32},
                                                        {32 * 8, 0, 32, 32},
                                                        {32 * 9, 0, 32, 32},
                                                        {32 * 10, 0, 32, 32},
                                                        {32 * 11, 0, 32, 32},
                                                        {32 * 12, 0, 32, 32},
                                                        {32 * 13, 0, 32, 32},
                                                        {32 * 14, 0, 32, 32},
                                                        {32 * 15, 0, 32, 32}}});
        return entity;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

/* exception */
rclient::ClientEntityFactory::FactoryException::FactoryException(std::string &&perror)
    : error_msg{std::move(perror)}
{
}

const char *rclient::ClientEntityFactory::FactoryException::what() const noexcept
{
    return this->error_msg.c_str();
}
