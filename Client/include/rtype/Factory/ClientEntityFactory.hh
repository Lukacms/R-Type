/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** factory header file
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <exception>
#include <rtype/Components/AnimationComponent.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/ECSManager.hpp>
#include <vector>

using njson = nlohmann::json;

namespace rclient
{

    static const rtype::HealthComponent BASIC_HEALTH{100, 100};
    static const rtype::BoxColliderComponent BASIC_COLLIDER{66, 30};
    const rtype::utils::TextureRect TEXTURERECT_SHIP{0, 0, 33, 15};
    const rtype::utils::TextureRect TEXTURERECT_OTHER_PLAYER{0, 0, 32, 32};
    const sf::Vector2f ORIGIN_ENEMY{16.5, 7.5};
    static const std::string_view ENTITIES_PATH{"./assets/configs/entities.json"};

    /**
     * @class ClientEntityFactory
     * @brief Build entities from nlohmann::json config files
     *
     */
    class ClientEntityFactory
    {
            enum class Type { ENEMY, PLAYER, OTHER_PLAYER, BULLET };

        public:
            ClientEntityFactory() = default;
            ClientEntityFactory(ClientEntityFactory const &to_copy) = default;
            ClientEntityFactory(ClientEntityFactory &&to_move) = default;
            ~ClientEntityFactory() = default;
            ClientEntityFactory &operator=(ClientEntityFactory const &to_copy) = default;
            ClientEntityFactory &operator=(ClientEntityFactory &&to_move) = default;

            static size_t create(std::size_t entity, const std::string &type,
                                 rtype::ECSManager &ecs_manager);
            static size_t create_json(std::size_t entity, const std::string &type,
                                      rtype::ECSManager &ecs_manager);

            class FactoryException : public std::exception
            {
                public:
                    explicit FactoryException(std::string &&perror);
                    FactoryException(FactoryException const &to_copy) = default;
                    FactoryException(FactoryException &&to_move) = default;
                    ~FactoryException() override = default;
                    FactoryException &operator=(FactoryException const &to_copy) = default;
                    FactoryException &operator=(FactoryException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg;
            };

        private:
    };
} // namespace rclient
