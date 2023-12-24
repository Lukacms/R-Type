/*
** EPITECH PROJECT, 2023
** game
** File description:
** ServerEntityFactory
*/

#include <exception>
#include <rtype/ECSManager.hpp>
#include <string_view>

namespace rserver
{
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
            static size_t create_enemy(rtype::ECSManager &ecs_manager);
            static size_t create_player(rtype::ECSManager &ecs_manager);
            static size_t create_other_player(rtype::ECSManager &ecs_manager);
            static size_t create_bullet(rtype::ECSManager &ecs_manager);
    };
} // namespace rserver
