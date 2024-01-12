/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EntryPoint
*/

#include <memory>
#include <rtype/ECSManager.hpp>

#ifdef _WIN32
    #ifdef RTYPE_ECS_EXPORTS
        #define RTYPE_ECS_API __declspec(dllexport)
    #else
        #define RTYPE_ECS_API __declspec(dllimport)
    #endif
#else
#endif

#ifdef __linux

    #pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

extern "C" {
std::unique_ptr<rtype::ECSManager> entrypoint()
{
    return std::make_unique<rtype::ECSManager>();
}
}

#else

extern "C" {
void *entrypoint()
{
    auto *ecs{new rtype::ECSManager()};

    return static_cast<void *>(ecs);
}
}

#endif /* __linux */
