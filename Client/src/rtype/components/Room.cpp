/*
** EPITECH PROJECT, 2023
** components
** File description:
** Room
*/

#include "rtype/Components/SpriteComponent.hh"
#include <rtype/components/Room.hh>
#include <string>

/* ctor / dtor */
rclient::components::RoomInfos::RoomInfos(const unsigned int &pid)
    : title{BASE_TITLE_ROOM.data() + std::to_string(pid)}, id{pid}
{
}

/* methods */
void rclient::components::RoomInfos::display(rtype::IGraphicModule &graphics,
                                             rtype::SpriteComponent &box)
{
    // graphics.draw(box, {});
}

void rclient::components::RoomInfos::set_nb_players(const unsigned int &new_players)
{
    this->nb_players = new_players;
}
