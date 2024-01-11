#/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EntryPoint
*/

#include <memory>
#include <rtype/PhysicsManager.hh>

#ifdef __linux

    #pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

extern "C" {
std::unique_ptr<rtype::PhysicsManager> entrypoint()
{
    return std::make_unique<rtype::PhysicsManager>();
}
}

#else

extern "C" {
void * entrypoint()
{
    auto *physics{new rtype::PhysicsManager()};

    return static_cast<void *>(physics);
}
}

#endif /* __linux */