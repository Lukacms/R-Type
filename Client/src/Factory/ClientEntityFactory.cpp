/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** factory source file
*/

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
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
    } catch (FactoryException &e) {
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
        sprite[entity]->sprite.setTextureRect(TEXTURERECT_SHIP);
        sprite[entity]->sprite.setOrigin(ORIGIN_ENEMY.x, ORIGIN_ENEMY.y);
        sprite[entity]->sprite.setScale(-2, 2);
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
        sprite[entity]->sprite.setTextureRect(TEXTURERECT_SHIP);
        sprite[entity]->sprite.setScale(2, 2);
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
        /*tmp.texture.loadFromFile("../../assets/elements/012.png");
        tmp.sprite.setTexture(tmp.texture);*/
        tmp.sprite.setTextureRect(TEXTURERECT_OTHER_PLAYER);
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
        sprite[entity]->sprite.setScale(2, 2);
        collider.insert_at(entity, BASIC_COLLIDER);
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
