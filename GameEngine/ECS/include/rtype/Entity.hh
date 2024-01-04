//
// Created by kane on 27/11/23.
//

#pragma once

#include <string>

namespace rtype
{
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

} // namespace rtype
