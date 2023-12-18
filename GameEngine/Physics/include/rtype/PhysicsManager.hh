//
// Created by kane on 12/12/23.
//

#include <exception>
#include <rtype/ComponentManager.hpp>
#include <string_view>
#include <vector>

namespace rtype
{

    struct Collision {
            std::size_t entity{0};
            std::vector<std::size_t> collided{};
    };

    constexpr std::string_view EXCEPTION_OCCURED{"Exception occured in PhysicsManager."};

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

            class PhysicsException : std::exception
            {
                public:
                    PhysicsException() = default;
                    PhysicsException(PhysicsException const &to_copy) = default;
                    PhysicsException(PhysicsException &&to_move) = default;
                    ~PhysicsException() override = default;
                    PhysicsException &operator=(PhysicsException const &to_copy) = default;
                    PhysicsException &operator=(PhysicsException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
            };

        private:
            std::vector<Collision> m_collisions{};
    };
} // namespace rtype
