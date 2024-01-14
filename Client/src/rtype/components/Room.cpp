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
/**
 * @brief Constructor for RoomInfos class
 *
 * @param pid - const u_int &
 * @param font - string, path to text's font
 */
rclient::components::RoomInfos::RoomInfos(const unsigned int &pid, const std::string &font)
    : title{BASE_TITLE_ROOM.data() + std::to_string(pid)}, id{pid}
{
    this->text.font_path = font;
    this->text.colors = rtype::utils::Colors{255, 255, 255};
}

/* methods */
/**
 * @brief Display elements of a room from a starting position
 *
 * @param graphics - IGraphicModule &
 * @param sprite - Sprite &
 * @param trans - TransformComponent &
 */
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

/**
 * @brief Set the number of players in the room
 *
 * @param new_players - const u_int &
 */
void rclient::components::RoomInfos::set_nb_players(const unsigned int &new_players)
{
    this->nb_players = new_players;
}

/**
 * @brief Set the status of the room
 *
 * @param pstatus - const u_short & - is associated to a enum
 */
void rclient::components::RoomInfos::set_status(const unsigned short &pstatus)
{
    this->status = pstatus;
}

/**
 * @brief Get the room's id
 *
 * @return u_int
 */
unsigned int rclient::components::RoomInfos::get_id() const
{
    return this->id;
}

/**
 * @brief Get the room's status
 *
 * @return u_short
 */
unsigned short rclient::components::RoomInfos::get_status() const
{
    return this->status;
}

/**
 * @brief Get the room's number of players
 *
 * @return u_int
 */
unsigned int rclient::components::RoomInfos::get_nb_players() const
{
    return this->nb_players;
}

/**
 * @brief Get the limits of the rooms, with top, left, width and height
 *
 * @return FloatRect
 */
sf::FloatRect rclient::components::RoomInfos::get_box() const
{
    return this->box;
}
