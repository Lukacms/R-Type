/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Lounge
*/

#include <algorithm>
#include <rtype/Client.hh>
#include <rtype/scenes/Lounge.hh>

/* ctor / dtor */
rclient::scenes::Lounge::Lounge(const unsigned int &pwidth, const unsigned int &pheight)
    : width{pwidth}, height{pheight}
{
}

/* methods */
void rclient::scenes::Lounge::draw(rtype::GraphicModule &graphics, rtype::utils::Clock &clock)
{
    if (clock.get_elapsed_time_in_ms() > GAME_TIMEOUT) {
        graphics.clear();
        graphics.display();
    }
}
