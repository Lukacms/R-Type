/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** SystemManager
*/

#pragma once

#include <functional>
#include <rtype/ComponentManager.hpp>
#include <vector>

class SystemManager
{
    public:
        SystemManager() = default;
        SystemManager(SystemManager const &to_copy) = default;
        SystemManager(SystemManager &&to_move) = default;
        ~SystemManager() = default;
        SystemManager &operator=(SystemManager const &to_copy) = default;
        SystemManager &operator=(SystemManager &&to_move) = default;

        std::function<void(ComponentManager &, float)> &
        add_system(std::function<void(ComponentManager &, float)> &function);
        void update(ComponentManager &registry, float delta_time);

    private:
        std::vector<std::function<void(ComponentManager &, float)>> m_systems;
};
