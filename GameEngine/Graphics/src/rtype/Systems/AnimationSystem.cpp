/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** AnimationSystem
*/

#include <rtype/ComponentManager.hpp>
#include <rtype/Components/AnimationComponent.hh>

namespace rtype
{

    void animation_system(ComponentManager &registry, float delta_time)
    {
        auto animator{registry.get_components<AnimationComponent>()};
    }

} // namespace rtype
