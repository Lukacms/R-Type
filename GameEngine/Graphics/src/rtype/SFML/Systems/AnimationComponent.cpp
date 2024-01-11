/*
** EPITECH PROJECT, 2023
** Systems
** File description:
** AnimationComponent
*/

#include <algorithm>
#include <rtype/Components/AnimationComponent.hh>

rtype::AnimationComponent::AnimationComponent(std::size_t pframe, std::string panim,
                                              utils::Clock pclock, std::vector<AnimationClip> pclip)
    : current_frame{std::move(pframe)}, current_animation{std::move(panim)},
      clock{std::move(pclock)}, animation_clips{std::move(pclip)}
{
}

rtype::AnimationComponent::AnimationComponent(const nlohmann::json &json)
{
    if (!json["current"].is_null())
        this->current_animation = json["current"];
    if (!json["frame"].is_null())
        this->current_frame = json["frame"];
    if (!json["clips"].is_null()) {
        for (const auto &clip : json["clips"])
            this->animation_clips.emplace_back(clip);
    }
}

/* AnimationClip */
rtype::AnimationClip::AnimationClip(const nlohmann::json &json)
{
    if (!json["name"].is_null())
        this->animation_name = json["name"];
    if (!json["loop"].is_null())
        this->is_loop = json["loop"];
    if (!json["change"].is_null())
        this->time_after_change = json["change"];
    if (!json["textures"].is_null()) {
        for (const auto &text : json["textures"])
            this->texture_rects.emplace_back(text);
    }
}

rtype::AnimationClip::AnimationClip(std::string panim, bool ploop, double ptime,
                                    std::vector<utils::TextureRect> ptexts)
    : animation_name{std::move(panim)}, is_loop{std::move(ploop)},
      time_after_change{std::move(ptime)}, texture_rects{std::move(ptexts)}
{
}
