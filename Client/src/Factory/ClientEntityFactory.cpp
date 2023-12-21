/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** factory source file
*/

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Factory/ClientEntityFactory.hh>

size_t rclient::ClientEntityFactory::create(std::size_t entity, const std::string &type,
                                            rtype::ECSManager &ecs_manager)
{
    std::size_t new_entity = ecs_manager.create_entity(entity);

    if (type == "Enemy") {
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
    tag.insert_at(entity, rtype::TagComponent{"Enemy"});
    rtype::SpriteComponent tmp{};
    /*tmp.texture.loadFromFile("Client/assets/elements/014.png");
    tmp.sprite.setTexture(tmp.texture);*/
    sf::IntRect rect(0, 0, 32, 32);
    tmp.sprite.setTextureRect(rect);
    sprite.insert_at(entity, rtype::SpriteComponent{tmp});
    return entity;
}

size_t rclient::ClientEntityFactory::create_player(std::size_t entity,
                                                   rtype::ECSManager &ecs_manager)
{
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    transform.insert_at(entity, rtype::TransformComponent{});
    tag.insert_at(entity, rtype::TagComponent{"Player"});
    rtype::SpriteComponent tmp;
    sprite.insert_at(entity, rtype::SpriteComponent{tmp});
    sprite[entity]->texture_path = "./Client/assets/Spaceship.png";
    sprite[entity]->sprite.setTextureRect({0, 0, 33, 15});
    sprite[entity]->sprite.setScale(2, 2);
    return entity;
}

size_t rclient::ClientEntityFactory::create_other_player(std::size_t entity,
                                                         rtype::ECSManager &ecs_manager)
{
    auto &health{ecs_manager.get_components<rtype::HealthComponent>()};
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};

    health.insert_at(entity, rtype::HealthComponent{100, 100});
    transform.insert_at(entity, rtype::TransformComponent{});
    tag.insert_at(entity, rtype::TagComponent{"OtherPlayer"});
    rtype::SpriteComponent tmp;
    /*tmp.texture.loadFromFile("../../assets/elements/012.png");
    tmp.sprite.setTexture(tmp.texture);*/
    sf::IntRect rect(0, 0, 32, 32);
    tmp.sprite.setTextureRect(rect);
    sprite.insert_at(entity, rtype::SpriteComponent{tmp});
    return entity;
}

size_t rclient::ClientEntityFactory::create_bullet(std::size_t entity,
                                                   rtype::ECSManager &ecs_manager)
{
    auto &transform{ecs_manager.get_components<rtype::TransformComponent>()};
    auto &tag{ecs_manager.get_components<rtype::TagComponent>()};
    auto &sprite{ecs_manager.get_components<rtype::SpriteComponent>()};

    transform.insert_at(entity, rtype::TransformComponent{});
    tag.insert_at(entity, rtype::TagComponent{"Bullet"});
    rtype::SpriteComponent tmp;
    sprite.insert_at(entity, rtype::SpriteComponent{tmp});
    sprite[entity]->texture_path = "./Client/assets/PlayerShoot.png";
    sprite[entity]->sprite.setScale(2, 2);
    return entity;
}
