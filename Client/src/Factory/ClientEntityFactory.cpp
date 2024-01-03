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
        std::cout << "UPGRADE HERE" << std::endl;
        return create_upgrade(new_entity, ecs_manager);
    }
    throw std::runtime_error("Unknown entity type");
}

size_t rclient::ClientEntityFactory::create_enemy(std::size_t entity,
                                                  rtype::ECSManager &ecs_manager)
{
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    transform.insert_at(entity, rtype::TransformComponent{});
    tag.insert_at(entity, rtype::TagComponent{"BasicEnemy"});
    sprite.insert_at(entity, rtype::SpriteComponent{});
    sprite[entity]->texture_path = "./Client/assets/BasicEnemy.png";
    sprite[entity]->sprite.setTextureRect({0, 0, 33, 15});
    sprite[entity]->sprite.setOrigin(16.5, 7.5);
    sprite[entity]->sprite.setScale(-2, 2);
    return entity;
}

size_t rclient::ClientEntityFactory::create_player(std::size_t entity,
                                                   rtype::ECSManager &ecs_manager)
{
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    transform.insert_at(entity, rtype::TransformComponent{});
    tag.insert_at(entity, rtype::TagComponent{"Player"});
    sprite.insert_at(entity, rtype::SpriteComponent{});
    sprite[entity]->texture_path = "./Client/assets/Spaceship.png";
    sprite[entity]->sprite.setTextureRect({0, 0, 33, 15});
    sprite[entity]->sprite.setScale(2, 2);
    collider.insert_at(entity, {66, 30});
    return entity;
}

size_t rclient::ClientEntityFactory::create_other_player(std::size_t entity,
                                                         rtype::ECSManager &ecs_manager)
{
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    transform.insert_at(entity, rtype::TransformComponent{});
    tag.insert_at(entity, rtype::TagComponent{"OtherPlayer"});
    rtype::SpriteComponent tmp;
    /*tmp.texture.loadFromFile("../../assets/elements/012.png");
    tmp.sprite.setTexture(tmp.texture);*/
    sf::IntRect rect(0, 0, 32, 32);
    tmp.sprite.setTextureRect(rect);
    sprite.insert_at(entity, rtype::SpriteComponent{tmp});
    collider.insert_at(entity, {66, 30});
    return entity;
}

size_t rclient::ClientEntityFactory::create_bullet(std::size_t entity,
                                                   rtype::ECSManager &ecs_manager)
{
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};

    transform.insert_at(entity, rtype::TransformComponent{});
    tag.insert_at(entity, rtype::TagComponent{"Bullet"});
    sprite.insert_at(entity, rtype::SpriteComponent{});
    sprite[entity]->texture_path = "./Client/assets/PlayerShoot.png";
    sprite[entity]->sprite.setScale(2, 2);
    collider.insert_at(entity, {66, 30});
    return entity;
}

size_t rclient::ClientEntityFactory::create_upgrade(std::size_t entity, rtype::ECSManager &ecs_manager)
{
    auto &collider{ecs_manager.get_components<rtype::BoxColliderComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprites{ecs_manager.get_components<rtype::SpriteComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};

    collider.insert_at(entity, rtype::BoxColliderComponent{});
    tag.insert_at(entity, rtype::TagComponent{"Upgrade"});
    transform.insert_at(entity, rtype::TransformComponent{});
    sprites.insert_at(entity, rtype::SpriteComponent{});
    sprites[entity]->texture_path = "./Client/assets/Upgrade.png";
    sprites[entity]->sprite.setScale(2, 2);
    sprites[entity]->sprite.setTextureRect({0, 0, 18, 18});
    return entity;
}
