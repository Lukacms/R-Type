/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EntityManager
*/

#include <rtype/EntityManager.hh>

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
            m_queue.erase(m_queue.begin() + static_cast<long>(i));
        }
    if (!exist)
        throw EntityException("Entity already assigned.");
    m_used.emplace_back(entity);
    return entity;
}

void rtype::EntityManager::delete_entity(size_t entity)
{
    m_queue.emplace_back(entity);
    for (auto iterator = m_used.cbegin(); iterator != m_used.cend(); iterator += 1) {
        if (*iterator == entity) {
            iterator = m_used.erase(iterator);
            return;
        }
    }
}

bool rtype::EntityManager::is_entity_used(std::size_t entity)
{
    for (auto used : m_used) // NOLINT
        if (used == entity)
            return true;
    return false;
}

std::vector<size_t> &rtype::EntityManager::get_used_entity()
{
    return m_used;
}

/* exception */
rtype::EntityManager::EntityException::EntityException(std::string &&perror)
    : error_msg{std::move(perror)}
{
}

const char *rtype::EntityManager::EntityException::what() const noexcept
{
    return this->error_msg.c_str();
}
