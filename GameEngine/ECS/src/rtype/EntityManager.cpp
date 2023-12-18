//
// Created by kane on 06/12/23.
//

#include <rtype/EntityManager.hh>
#include <stdexcept>

rtype::EntityManager::EntityManager()
{
    for (size_t i = 1; i <= MAX_ENTITIES; i += 1)
        m_queue.emplace_back(i);
}

size_t rtype::EntityManager::create_entity()
{
    size_t new_entity{m_queue.front()};

    m_queue.erase(m_queue.begin());
    return new_entity;
}

size_t rtype::EntityManager::create_entity(size_t entity)
{
    bool exist{false};

    for (size_t i{0}; i < m_queue.size(); i++)
        if (m_queue[i] == entity) {
            exist = true;
            m_queue.erase(m_queue.begin() + i);
        }
    if (!exist)
        throw std::runtime_error("entity already assign");
    return entity;
}

void rtype::EntityManager::delete_entity(size_t entity)
{
    m_queue.emplace_back(entity);
}
