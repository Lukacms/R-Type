/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EntityManager
*/

#include <cstddef>
#include <exception>
#include <string>
#include <vector>

namespace rtype
{
    const constexpr std::size_t MAX_ENTITIES{10000};

    class EntityManager
    {
        public:
            EntityManager();
            EntityManager(EntityManager const &to_copy) = default;
            EntityManager(EntityManager &&to_move) = default;
            ~EntityManager() = default;
            EntityManager &operator=(EntityManager const &to_copy) = default;
            EntityManager &operator=(EntityManager &&to_move) = default;

            size_t create_entity();
            size_t create_entity(size_t entity);
            bool is_entity_used(std::size_t entity);
            void delete_entity(size_t entity);
            std::vector<std::size_t> &get_used_entity();

            class EntityException : public std::exception
            {
                public:
                    EntityException(std::string &&perror = "Error");
                    EntityException(EntityException const &to_copy) = default;
                    EntityException(EntityException &&to_move) = default;
                    ~EntityException() override = default;
                    EntityException &operator=(EntityException const &to_copy) = default;
                    EntityException &operator=(EntityException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg{};
            };

        private:
            std::vector<std::size_t> m_queue{};
            std::vector<std::size_t> m_used{};
    };
} // namespace rtype
