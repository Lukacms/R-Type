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

/**
 * @brief Create function. Call private create_json function
 *
 * @param entity - size_t
 * @param type - const string &
 * @param ecs_manager - ECSManager &
 * @return id to entity - size_t
 */
std::size_t rclient::ClientEntityFactory::create(std::size_t entity, const std::string &type,
                                                 rtype::ECSManager &ecs_manager)
{
    try {
        return create_json(entity, type, ecs_manager);
    } catch (FactoryException &e) {
        throw e;
    } catch (rtype::ECSManager::ECSException &e) {
        throw FactoryException(e.what());
    }
}

/**
 * @brief Building client's entity from server's entity id and nlohmann::json configuration file
 *
 * @param entity - size_t
 * @param type - const string &
 * @param ecs_manager - ECSManager &
 * @return id to constructed entity - size_t
 */
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

/* exception */
rclient::ClientEntityFactory::FactoryException::FactoryException(std::string &&perror)
    : error_msg{std::move(perror)}
{
}

const char *rclient::ClientEntityFactory::FactoryException::what() const noexcept
{
    return this->error_msg.c_str();
}
