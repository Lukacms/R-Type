/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** AnimationSystem
*/

#include <iostream>
#include <rtype/ComponentManager.hpp>
#include <rtype/Components/AnimationComponent.hh>
#include <rtype/Components/SpriteComponent.hh>

namespace rtype
{
    void animation_system(ComponentManager &registry, float /* delta_time */)
    {
        auto &animations = registry.get_components<AnimationComponent>();
        auto &sprites = registry.get_components<SpriteComponent>();

        for (std::size_t entity = 0; entity < animations.size() && entity < sprites.size();
             entity += 1) {
            if (!animations[entity].has_value() || !sprites[entity].has_value())
                continue;
            for (auto &clip : animations[entity]->animation_clips) {
                if (clip.animation_name != animations[entity]->current_animation ||
                    clip.time_after_change > animations[entity]->clock.get_elapsed_time_in_ms())
                    continue;
                animations[entity]->current_frame += 1;
                if (animations[entity]->current_frame >= clip.texture_rects.size() && clip.is_loop)
                    animations[entity]->current_frame = 0;
                else if (!clip.is_loop)
                    animations[entity]->current_frame = clip.texture_rects.size() - 1;
                sprites[entity]->rectangle = clip.texture_rects[animations[entity]->current_frame];
                animations[entity]->clock.reset();
            }
        }
    }

} // namespace rtype
