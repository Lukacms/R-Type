/*
** EPITECH PROJECT, 2023
** Graphics
** File description:
** AnimationComponent
*/

#pragma once

#include <nlohmann/json.hpp>
#include <rtype/ComponentManager.hpp>
#include <rtype/utils/Clock.hh>
#include <rtype/utils/Vector2D.hh>
#include <vector>

namespace rtype
{
    struct AnimationClip {
            std::string animation_name;
            bool is_loop{false};
            double time_after_change;
            std::vector<rtype::utils::TextureRect> texture_rects;

            AnimationClip(std::string panim = "", bool ploop = false, double ptime = 0,
                          std::vector<utils::TextureRect> ptexts = {});
            AnimationClip(const AnimationClip &to_copy) = default;
            AnimationClip(AnimationClip &&to_move) = default;
            AnimationClip &operator=(const AnimationClip &to_copy) = default;
            AnimationClip &operator=(AnimationClip &&to_move) = default;

            /* njson */
            AnimationClip(const nlohmann::json &json);
    };

    struct AnimationComponent {
        public:
            std::size_t current_frame{0};
            std::string current_animation{};
            rtype::utils::Clock clock;
            std::vector<AnimationClip> animation_clips{};

            AnimationComponent(std::size_t pframe = 0, std::string panim = "",
                               utils::Clock pclock = {}, std::vector<AnimationClip> pclip = {});
            /* njson */
            AnimationComponent(const nlohmann::json &json);
    };

    void animation_system(ComponentManager &registry, float /* delta_time */);

} // namespace rtype
