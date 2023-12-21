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
    m_used.emplace_back(new_entity);
    return new_entity;
}

size_t rtype::EntityManager::create_entity(size_t entity)
{
    bool exist{false};

    for (size_t i{0}; i < m_queue.size(); i++)
        if (m_queue[i] == entity) {
            exist = true;
            m_queue.erase(m_queue.begin() + static_cast<ssize_t>(i));
        }
    if (!exist)
        throw std::runtime_error("entity already assign");
    m_used.emplace_back(entity);
    return entity;
}

void rtype::EntityManager::delete_entity(size_t entity)
{
    m_queue.emplace_back(entity);
    for (auto iterator = m_used.cbegin(); iterator != m_used.cend(); iterator += 1) {
        if (*iterator == entity) {
            iterator = m_used.erase(iterator);
        }
    }
}

bool rtype::EntityManager::is_entity_used(std::size_t entity)
{
    for (auto used : m_used)
        if (used == entity)
            return true;
    return false;
}
