/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Components
*/

#include <algorithm>
#include <iostream>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TransformComponent.hh>

/* BoxColliderComponent */
rtype::BoxColliderComponent &rtype::BoxColliderComponent::operator=(const nlohmann::json &json)
{
    this->width = json["width"];
    this->height = json["height"];
    return *this;
}

rtype::BoxColliderComponent::BoxColliderComponent(const nlohmann::json &json)
{
    this->width = json["width"];
    this->height = json["height"];
}

rtype::BoxColliderComponent::BoxColliderComponent(float pwidth, float pheigth)
    : width{std::move(pwidth)}, height{std::move(pheigth)}
{
}

/* HealthComponent */
rtype::HealthComponent &rtype::HealthComponent::operator=(const nlohmann::json &json)
{
    this->health = json["health"];
    this->max_health = json["maxHealth"];
    return *this;
}

rtype::HealthComponent::HealthComponent(const nlohmann::json &json)
{
    this->health = json["health"];
    this->max_health = json["maxHealth"];
}

rtype::HealthComponent::HealthComponent(int phealth, int pmax_health)
    : health{std::move(phealth)}, max_health{std::move(pmax_health)}
{
}

/* TransformComponent */
rtype::TransformComponent &rtype::TransformComponent::operator=(const nlohmann::json &json)
{
    this->scale_x = json["scale"]["x"];
    this->scale_y = json["scale"]["y"];
    this->position_x = json["position"]["x"];
    this->position_y = json["position"]["y"];
    this->velocity_x = json["velocity"]["x"];
    this->velocity_y = json["velocity"]["y"];
    return *this;
}

rtype::TransformComponent::TransformComponent(const nlohmann::json &json)
{
    this->scale_x = json["scale"]["x"];
    this->scale_y = json["scale"]["y"];
    this->position_x = json["position"]["x"];
    this->position_y = json["position"]["y"];
    this->velocity_x = json["velocity"]["x"];
    this->velocity_y = json["velocity"]["y"];
}

rtype::TransformComponent::TransformComponent(float pposition_x, float pposition_y,
                                              float pvelocity_x, float pvelocity_y, float pscale_x,
                                              float pscale_y)
    : position_x{std::move(pposition_x)}, position_y{std::move(pposition_y)},
      velocity_x{std::move(pvelocity_x)}, velocity_y{std::move(pvelocity_y)},
      scale_x{std::move(pscale_x)}, scale_y{std::move(pscale_y)}
{
}
