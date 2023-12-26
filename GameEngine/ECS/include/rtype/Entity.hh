//
// Created by kane on 27/11/23.
//

#include <string>

class Entity
{
    public:
        Entity(std::size_t &&index);
        ~Entity() = default;
        Entity(const Entity &) = default;
        Entity(Entity &&) = default;
        Entity &operator=(const Entity &) = default;
        Entity &operator=(Entity &&) = default;

        operator std::size_t() const;

    private:
        std::size_t m_id{};
};
