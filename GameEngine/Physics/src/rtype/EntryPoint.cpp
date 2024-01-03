#/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EntryPoint
*/

#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

#include <memory>
#include <rtype/PhysicsManager.hh>

extern "C" {
std::unique_ptr<rtype::PhysicsManager> entrypoint()
{
    return std::make_unique<rtype::PhysicsManager>();
}
}
