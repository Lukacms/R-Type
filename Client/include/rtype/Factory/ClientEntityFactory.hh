/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** factory header file
*/

#pragma once

#include <array>
#include <rtype/ECSManager.hpp>
#include <vector>

namespace rclient
{

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

        private:
            static size_t create_enemy(std::size_t entity, rtype::ECSManager &ecs_manager);
            static size_t create_player(std::size_t entity, rtype::ECSManager &ecs_manager);
            static size_t create_other_player(std::size_t entity, rtype::ECSManager &ecs_manager);
            static size_t create_bullet(std::size_t entity, rtype::ECSManager &ecs_manager);
    };
} // namespace rclient
