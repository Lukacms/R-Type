/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EntryPoint
*/

#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

#include <memory>
#include <rtype/ECSManager.hpp>

extern "C" {
std::unique_ptr<rtype::ECSManager> entrypoint()
{
    return std::make_unique<rtype::ECSManager>();
}
}
