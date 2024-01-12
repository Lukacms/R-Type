/*
** EPITECH PROJECT, 2023
** game
** File description:
** ServerEntityFactory
*/

#pragma once

#include <exception>
#include <nlohmann/json.hpp>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <string_view>

using njson = nlohmann::json;

namespace rserver
{
    static const rtype::HealthComponent BASIC_HEALTH{100, 100};
    static const rtype::BoxColliderComponent BASIC_COLLIDER{33, 15};
    static const rtype::BoxColliderComponent COLLIDER_BULLET{33, 15};
    static const rtype::TransformComponent TRANS_PLAYER{300, 400, 0, 0, 2, 2};
    static const rtype::TransformComponent TRANS_ENEMY{850, 300, -0.1F, 0, 2, 2};
    static const rtype::TransformComponent TRANS_BULLET{0, 0, 0, 0, 2, 2};
    static const rtype::BoxColliderComponent KAMIKAZE_COLLIDER{18, 18};
    static const std::string_view ENTITIES_PATH{"./assets/configs/entities.json"};
    constexpr float VELOCITY_BULLET{0.15F};

    /**
     * @class ServerEntityFactory
     * @brief To create entities and register them with the ECS
     *  They load the entities through a .json file containing all infos of the entities
     *
     */
    class ServerEntityFactory
    {

        public:
            ServerEntityFactory() = default;
            ~ServerEntityFactory() = default;
            ServerEntityFactory(const ServerEntityFactory &factory) = default;
            ServerEntityFactory(ServerEntityFactory &&factory) = default;
            ServerEntityFactory &operator=(const ServerEntityFactory &factory) = default;
            ServerEntityFactory &operator=(ServerEntityFactory &&factory) = default;

            class FactoryException : public std::exception
            {
                public:
                    FactoryException(std::string &&perror_msg = "Error");
                    FactoryException(FactoryException const &to_copy) = default;
                    FactoryException(FactoryException &&to_move) = default;
                    ~FactoryException() override = default;
                    FactoryException &operator=(FactoryException const &to_copy) = default;
                    FactoryException &operator=(FactoryException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg{};
            };

            static size_t create(const std::string &type, rtype::ECSManager &ecs_manager);

        private:
            static size_t create_json(const std::string &type, rtype::ECSManager &ecs_manager);
    };
} // namespace rserver
