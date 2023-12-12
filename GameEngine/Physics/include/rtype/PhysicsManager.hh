//
// Created by kane on 12/12/23.
//

#include <rtype/ComponentManager.hpp>
#include <vector>

namespace rtype
{

    struct Collision {
            std::size_t entity{0};
            std::vector<std::size_t> collided{};
    };

    class PhysicsManager
    {
        public:
            PhysicsManager() = default;
            PhysicsManager(PhysicsManager const &to_copy) = default;
            PhysicsManager(PhysicsManager &&to_move) = default;
            ~PhysicsManager() = default;
            PhysicsManager &operator=(PhysicsManager const &to_copy) = default;
            PhysicsManager &operator=(PhysicsManager &&to_move) = default;

            void check_collisions(ComponentManager &component_manager);
            [[nodiscard]] std::vector<std::size_t> get_collision(std::size_t entity) const;
            [[nodiscard]] bool is_collided(std::size_t entity1, std::size_t entity2) const;

        private:
            std::vector<Collision> m_collisions{};
    };
} // namespace rtype
