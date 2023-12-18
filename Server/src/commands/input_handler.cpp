/*
** EPITECH PROJECT, 2023
** commands
** File description:
** input_handler
*/

#include "rtype.hh"
#include <array>
#include <iostream>
#include <rtype/Components/TransformComponent.hh>
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

    if (args.size() != 1 || !(is_number(args[0])) || args[0][0] < '0' || args[0][0] > '3') {
        throw ManagerException{WRONG_ARGUMENTS.data()};
    }

    component.position_x += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_x;
    component.position_y += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_y;
    std::cout << "pos x: " << component.position_x << ", pos_y: " << component.position_y << ENDL;
}
