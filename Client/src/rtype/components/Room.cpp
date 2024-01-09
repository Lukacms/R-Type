/*
** EPITECH PROJECT, 2023
** components
** File description:
** Room
*/

#include <rtype/Components/SpriteComponent.hh>
#include <rtype/components/Room.hh>
#include <string>

/* ctor / dtor */
rclient::components::RoomInfos::RoomInfos(const unsigned int &pid, sf::Font &font)
    : title{BASE_TITLE_ROOM.data() + std::to_string(pid)}, id{pid}
{
    this->text.setFont(font);
    this->text.setFillColor(sf::Color::White);
}

/* methods */
void rclient::components::RoomInfos::display(rtype::IGraphicModule &graphics, sf::Sprite &box,
                                             rtype::TransformComponent &trans)
{
    auto pos_y{trans.position_y};
    auto pos_x{trans.position_x};

    graphics.draw(box, trans);
    this->text.setString(this->title);
    this->text.setCharacterSize(20);
    trans.position_y -= TRANS_POS;
    trans.position_x += TRANS_POS + 20;
    graphics.draw(this->text, trans);
    trans.position_x += TRANS_POS * 9;
    this->text.setString(std::to_string(this->nb_players) + " / 4");
    graphics.draw(this->text, trans);
    this->text.setCharacterSize(30);
    trans.position_x -= TRANS_POS * 5;
    trans.position_y += TRANS_POS / 2;
    this->text.setString(this->statuses[this->status]);
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
