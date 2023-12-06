/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EntityManager
*/

#include <deque>

namespace rtype
{
    const constexpr size_t MAX_ENTITIES{10000};

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
            void delete_entity(size_t entity);

        private:
            std::deque<size_t> m_queue{};
    };
} // namespace rtype
