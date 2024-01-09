/*
** EPITECH PROJECT, 2023
** src
** File description:
** utils
*/

#include <rtype.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/ClockComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/utils.hpp>
#include <rtype/GameLogic/GameLogic.hh>
#include <sstream>
#include <string>

/**
 * @brief check if a string is composed only of numbers
 *
 * @param str-  string - to analyse
 * @return bool
 */
bool rserver::is_number(std::string const &str)
{
    return str.find_first_not_of(NUMBERS) == std::string::npos;
}

/**
 * @brief Split a string into a vector of string depending on the delimitors given
 *
 * @param src - string - to split
 * @param del - string - used to delimit parse
 * @return vector<string> that may be empty on error
 */
std::vector<std::string> rserver::split_delimitor(std::string &src, const std::string &del)
{
    std::vector<std::string> dest{};
    size_t pos{0};

    while ((pos = src.find_first_of(del)) != std::string::npos) {
        dest.emplace_back(src.substr(0, pos));
        pos = src.find_first_not_of(del, pos);
        src.erase(0, pos);
    }
    if (!src.empty())
        dest.emplace_back(src);
    return dest;
}

/**
 * @brief Split a string into a vector of string depending on the delimitors given
 *
 * @param src - string - to split; is given as copy instead of ref to construct it during the
 * prototype
 * @param del - string - used to delimit parse
 * @return vector<string> that may be empty on error
 */
std::vector<std::string> rserver::split_delimitor(std::string src, const std::string &del)
{
    std::vector<std::string> dest{};
    size_t pos{0};

    while ((pos = src.find_first_of(del)) != std::string::npos) {
        dest.emplace_back(src.substr(0, pos));
        pos = src.find_first_not_of(del, pos);
        src.erase(0, pos);
    }
    if (!src.empty())
        dest.emplace_back(src);
    return dest;
}

/**
 * @brief Init an ECS with SparseArray for TransformComponent, BoxColliderComponent, TagComponent,
 * HealthComponent, and transform_system
 *
 * @param to_load - ECSManager
 */
void rserver::init_ecs(rtype::ECSManager &to_load)
{
    rtype::SparseArray<rtype::TransformComponent> transform{};
    rtype::SparseArray<rtype::BoxColliderComponent> boxes{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::HealthComponent> healths{};
    rtype::SparseArray<rtype::ClockComponent> clocks{};
    std::function<void(rtype::ComponentManager &, float)> transform_system{
        &rtype::transform_system};
    std::function<void(rtype::ComponentManager &, float)> kamikaze_system{
        &game::kamikaze_system};

    to_load.register_component(transform);
    to_load.register_component(boxes);
    to_load.register_component(tags);
    to_load.register_component(healths);
    to_load.register_component(clocks);
    to_load.add_system(transform_system);
    to_load.add_system(kamikaze_system);
}
