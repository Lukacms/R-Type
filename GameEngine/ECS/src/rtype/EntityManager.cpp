//
// Created by kane on 06/12/23.
//

#include <rtype/EntityManager.hh>

rtype::EntityManager::EntityManager()
{
    for (size_t i = 1; i <= MAX_ENTITIES; i += 1)
        m_queue.emplace_back(i);
}

size_t rtype::EntityManager::create_entity()
{
    size_t new_entity{m_queue.front()};

    m_queue.pop_front();
    return new_entity;
}

void rtype::EntityManager::delete_entity(size_t entity)
{
    m_queue.emplace_back(entity);
}
