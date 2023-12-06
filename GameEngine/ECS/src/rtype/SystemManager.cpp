/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** SystemManager
*/

#include "rtype/SystemManager.hh"

constexpr std::function<void(Registry &)> &
SystemManager::add_system(std::function<void(Registry &)> &function)
{
    m_systems.emplace_back(function);
    return m_systems[m_systems.size() - 1];
}

constexpr void SystemManager::update(Registry &registry, double delta_time)
{
    for (size_t i{0}; i < m_systems.size(); i++)
        m_systems[i](registry);
}
