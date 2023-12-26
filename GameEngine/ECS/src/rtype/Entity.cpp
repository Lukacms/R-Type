//
// Created by kane on 27/11/23.
//

#include <rtype/Entity.hh>

rtype::Entity::Entity(std::size_t &&index) : m_id{std::move(index)}
{
}

rtype::Entity::operator std::size_t() const
{
    return m_id;
}
