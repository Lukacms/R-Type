//
// Created by kane on 27/11/23.
//

#include <rtype/Entity.hh>

Entity::Entity(std::size_t &&index) : m_id{std::move(index)}
{
}

Entity::operator std::size_t() const
{
    return m_id;
}
