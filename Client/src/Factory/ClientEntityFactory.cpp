/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** factory source file
*/

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
        std::size_t new_entity = ecs_manager.create_entity(entity);

        if (type == "BasicEnemy") {
            return create_enemy(new_entity, ecs_manager);
        }
        if (type == "Player") {
            return create_player(new_entity, ecs_manager);
        }
        if (type == "OtherPlayer") {
            return create_other_player(new_entity, ecs_manager);
        }
        if (type == "Bullet") {
            return create_bullet(new_entity, ecs_manager);
        }
        if (type == "Upgrade") {
            return create_upgrade(new_entity, ecs_manager);
        }
    } catch (FactoryException &e) {
        throw e;
    } catch (rtype::ECSManager::ECSException &e) {
        throw e;
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
        sprite[entity]->texture_path = "./Client/assets/BasicEnemy.png";
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
        sprite[entity]->texture_path = "./Client/assets/Spaceship.png";
        sprite[entity]->rectangle = TEXTURERECT_SHIP;
        transform[entity]->scale_x = 2;
        transform[entity]->scale_y = 2;
        collider.insert_at(entity, BASIC_COLLIDER);
        return entity;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

size_t rclient::ClientEntityFactory::create_other_player(std::size_t entity,
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
        tag.insert_at(entity, rtype::TagComponent{"OtherPlayer"});
        rtype::SpriteComponent tmp;
        sprite[entity]->rectangle = TEXTURERECT_OTHER_PLAYER;
        sprite.insert_at(entity, rtype::SpriteComponent{tmp});
        collider.insert_at(entity, BASIC_COLLIDER);
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
        tag.insert_at(entity, rtype::TagComponent{"Bullet"});
        sprite.insert_at(entity, rtype::SpriteComponent{});
        sprite[entity]->texture_path = "./Client/assets/PlayerShoot.png";
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
        animations[entity]->animation_clips.push_back({.animation_name = "Idle",
                                                       .is_loop = true,
                                                       .time_after_change = 50,
                                                       .texture_rects = {{0, 0, 17, 17},
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

/* exception */
rclient::ClientEntityFactory::FactoryException::FactoryException(std::string &&perror)
    : error_msg{std::move(perror)}
{
}

const char *rclient::ClientEntityFactory::FactoryException::what() const noexcept
{
    return this->error_msg.c_str();
}
