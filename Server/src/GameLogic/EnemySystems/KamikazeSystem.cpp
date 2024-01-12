//
// Created by kane on 09/01/24.
//

#include <algorithm>
#include <cmath>
#include <rtype/ComponentManager.hpp>
#include <rtype/Components/ClockComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>

namespace rserver::game
{
    static void find_nearest_player(rtype::SparseArray<rtype::TransformComponent> &transforms,
                                    rtype::SparseArray<rtype::TagComponent> &tags,
                                    std::size_t enemy_entity)
    {
        std::vector<rtype::TransformComponent> players{};

        for (std::size_t entity = 0; entity < tags.size(); entity += 1) {
            if (!tags[entity].has_value() || !transforms[entity].has_value())
                continue;
            if (tags[entity]->tag == "Player")
                players.emplace_back(transforms[entity].value());
        }
        auto lambda = [&](rtype::TransformComponent &p1, rtype::TransformComponent &p2) -> bool {
            return std::sqrt(std::pow(p1.position_x - transforms[enemy_entity]->position_x, 2) +
                             std::pow(p1.position_y - transforms[enemy_entity]->position_y, 2)) <
                std::sqrt(std::pow(p2.position_x - transforms[enemy_entity]->position_x, 2) +
                          std::pow(p2.position_y - transforms[enemy_entity]->position_y, 2));
        };
        std::sort(players.begin(), players.end(), lambda);
        if (players.empty()) {
            transforms[enemy_entity]->velocity_x = std::rand() % 5 + 2 / 10;
            transforms[enemy_entity]->velocity_y = std::rand() % 5 + 2 / 10;
            return;
        }
        auto focused_player = players[0];
        auto magnitude = static_cast<float>(std::sqrt(
            std::pow(focused_player.position_x - transforms[enemy_entity]->position_x, 2) +
            std::pow(focused_player.position_y - transforms[enemy_entity]->position_y, 2)));
        transforms[enemy_entity]->velocity_x =
            (focused_player.position_x - transforms[enemy_entity]->position_x) / magnitude;
        transforms[enemy_entity]->velocity_y =
            (focused_player.position_y - transforms[enemy_entity]->position_y) / magnitude;
    }

    void kamikaze_system(rtype::ComponentManager &registry, float /* delta_time */)
    {
        auto &clocks = registry.get_components<rtype::ClockComponent>();
        auto &transforms = registry.get_components<rtype::TransformComponent>();
        auto &tags = registry.get_components<rtype::TagComponent>();

        for (std::size_t entity = 0; entity < tags.size(); entity += 1) {
            if (!tags[entity].has_value() || tags[entity]->tag != "KamikazeEnemy")
                continue;
            if (!clocks[entity].has_value() || !transforms[entity].has_value())
                continue;
            if (clocks[entity]->clock.get_elapsed_time_in_s() < 4) {
                if (transforms[entity]->position_x < 600)
                    transforms[entity]->velocity_x = 0;
                continue;
            }
            if (clocks[entity]->clock.get_elapsed_time_in_s() > 4) {
                if (transforms[entity]->velocity_x == 0.0F)
                    find_nearest_player(transforms, tags, entity);
            }
        }
    }
} // namespace rserver::game
