/*
** EPITECH PROJECT, 2023
** game
** File description:
** ServerEntityFactory
*/

#include <rtype/ECSManager.hpp>
#include <string_view>

class ServerEntityFactory
{

    public:
        ServerEntityFactory() = default;
        ~ServerEntityFactory() = default;
        ServerEntityFactory(const ServerEntityFactory &factory) = default;
        ServerEntityFactory(ServerEntityFactory &&factory) = default;
        ServerEntityFactory &operator=(const ServerEntityFactory &factory) = default;
        ServerEntityFactory &operator=(ServerEntityFactory &&factory) = default;

        static size_t create(const std::string &type, rtype::ECSManager &ecs_manager);

    private:
        static size_t create_enemy(rtype::ECSManager &ecs_manager);
        static size_t create_player(rtype::ECSManager &ecs_manager);
        static size_t create_other_player(rtype::ECSManager &ecs_manager);
        static size_t create_bullet(rtype::ECSManager &ecs_manager);
};
