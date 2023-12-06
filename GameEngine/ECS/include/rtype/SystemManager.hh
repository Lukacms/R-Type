/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** SystemManager
*/

#pragma once

#include "Registry.hpp"
#include <functional>
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

        constexpr std::function<void(Registry &)> &
        add_system(std::function<void(Registry &)> &function);
        constexpr void update(Registry &registry, double delta_time);

    private:
        std::vector<std::function<void(Registry &)>> m_systems;
};
