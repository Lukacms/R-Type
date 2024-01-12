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

/**
 * @brief Create a new entity and register it on the ECS
 *
 * @param type - string - typename of the entity
 * @param ecs_manager - ECSManager
 * @return size_t - id of the new entity
 */
size_t rserver::ServerEntityFactory::create(const std::string &type, rtype::ECSManager &ecs_manager)
{
    try {
        return create_json(type, ecs_manager);
    } catch (FactoryException &e) {
        throw e;
    }
}

/**
 * @brief Called by the method create. Read the "./assets/conigs/entities.json" file to register
 * entities
 *
 * @param type - string - typename of entity
 * @param ecs_manager - ECSManager
 * @return - size_t - id of entity
 */
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

/* exception */
rserver::ServerEntityFactory::FactoryException::FactoryException(std::string &&perror_msg)
    : error_msg{std::move(perror_msg)}
{
}

const char *rserver::ServerEntityFactory::FactoryException::what() const noexcept
{
    return this->error_msg.c_str();
}
