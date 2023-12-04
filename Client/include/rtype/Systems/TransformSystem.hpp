/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** transform_system
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <rtype/Registry.hpp>

class TransformSystem
{
    public:
        void update(Registry &registry);
};
