//
// Created by kane on 27/11/23.
//

#include <rtype/Entity.hh>

Entity::Entity(std::size_t id) : m_id{id}
{
}

Entity::operator std::size_t() const
{
    return m_id;
}
