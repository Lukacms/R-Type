/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** SystemManager
*/

#pragma once

#include <functional>
#include <rtype/Registry.hpp>
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

        std::function<void(Registry &)> &add_system(std::function<void(Registry &)> &function);
        void update(Registry &registry);

    private:
        std::vector<std::function<void(Registry &)>> m_systems;
};
