/*
** EPITECH PROJECT, 2023
** components
** File description:
** Room
*/

#include <iostream>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/components/Room.hh>
#include <string>

/* ctor / dtor */
rclient::components::RoomInfos::RoomInfos(const unsigned int &pid, const std::string &font)
    : title{BASE_TITLE_ROOM.data() + std::to_string(pid)}, id{pid}
{
    this->text.font_path = font;
    this->text.colors = rtype::utils::Colors::White;
}

/* methods */
void rclient::components::RoomInfos::display(rtype::IGraphicModule &graphics, sf::Sprite &sprite,
                                             rtype::TransformComponent &trans)
{
    auto pos_y{trans.position_y};
    auto pos_x{trans.position_x};

    graphics.draw(sprite, trans);
    this->box = sprite.getGlobalBounds();
    this->text.text = this->title;
    this->text.font_size = INFOS_SUBTITLE;
    trans.position_y -= POS1;
    trans.position_x += POS2;
    graphics.draw(this->text, trans);
    trans.position_x += POS3;
    this->text.text = std::to_string(this->nb_players) + " / 4";
    graphics.draw(this->text, trans);
    this->text.font_size = INFOS_TITLE;
    trans.position_x -= POS4;
    trans.position_y += POS5;
    this->text.text = this->statuses[this->status];
    graphics.draw(this->text, trans);
    trans.position_y = pos_y;
    trans.position_x = pos_x;
}

void rclient::components::RoomInfos::set_nb_players(const unsigned int &new_players)
{
    this->nb_players = new_players;
}

void rclient::components::RoomInfos::set_status(const unsigned short &pstatus)
{
    this->status = pstatus;
}

unsigned int rclient::components::RoomInfos::get_id() const
{
    return this->id;
}

unsigned short rclient::components::RoomInfos::get_status() const
{
    return this->status;
}

unsigned int rclient::components::RoomInfos::get_nb_players() const
{
    return this->nb_players;
}

sf::FloatRect rclient::components::RoomInfos::get_box() const
{
    return this->box;
}
