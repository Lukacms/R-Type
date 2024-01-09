/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Lounge
*/

#include <algorithm>
#include <rtype/scenes/Lounge.hh>

/* ctor / dtor */
rclient::scenes::Lounge::Lounge(const unsigned int &pwidth, const unsigned int &pheight)
    : width{pwidth}, height{pheight}
{
}

/* methods */
void rclient::scenes::Lounge::display(rtype::IGraphicModule &graphics)
{
    graphics.clear();
    for (auto &room : this->rooms) {
        room.display(graphics, this->sprite);
    }
    graphics.display();
}

void rclient::scenes::Lounge::handle_events(rtype::IGraphicModule &graphics,
                                            rtype::IAudioModule & /*audio*/, State &state)
{
}

void rclient::scenes::Lounge::handle_network(ntw::Communication &commn,
                                             rtype::IAudioModule & /*audio*/, State &state)
{
}
