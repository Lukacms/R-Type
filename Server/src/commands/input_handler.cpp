/*
** EPITECH PROJECT, 2023
** commands
** File description:
** input_handler
*/

#include <array>
#include <iostream>
#include <rtype.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/Manager.hh>
#include <vector>

static const std::array<rserver::Vector2f, 4> POSITIONS{{
    {.pos_x = 0, .pos_y = rserver::POSITION_CHANGE * -1},
    {.pos_x = rserver::POSITION_CHANGE, .pos_y = 0},
    {.pos_x = 0, .pos_y = rserver::POSITION_CHANGE},
    {.pos_x = rserver::POSITION_CHANGE * -1, .pos_y = 0},
}};

void rserver::Manager::input_handler(rserver::Player &player, std::vector<std::string> &args)
{
    auto &component{
        this->ecs.get_class().get_component<rtype::TransformComponent>(player.get_entity_value())};

    if (args.size() != 1 || !(is_number(args[0])) || args[0][0] < '0' || args[0][0] > '4') {
        throw ManagerException{WRONG_ARGUMENTS.data()};
    }
    if (args[0][0] == '4') {
        std::unique_lock<std::mutex> lock{this->ecs_mutex};
        size_t bullet_id{ServerEntityFactory::create("Bullet", this->ecs.get_class())};
        auto &transform_bullet{
            this->ecs.get_class().get_component<rtype::TransformComponent>(bullet_id)};
        transform_bullet.position_x = component.position_x + POSITION_CHANGE;
        transform_bullet.position_y = component.position_y;
        return;
    }
    component.position_x += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_x;
    component.position_y += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_y;
    DEBUG(("pos x: %f, pos_y: %f\n", static_cast<double>(component.position_x),
           static_cast<double>(component.position_y)));
}
