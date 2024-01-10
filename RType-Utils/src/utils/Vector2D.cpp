/*
** EPITECH PROJECT, 2023
** utils
** File description:
** Vector2D
*/

#include <algorithm>
#include <rtype/utils/Vector2D.hh>

rtype::utils::TextureRect::TextureRect(const nlohmann::json &json)
{
    this->x = json["x"];
    this->y = json["y"];
    this->width = json["width"];
    this->height = json["height"];
}

rtype::utils::TextureRect::TextureRect(int p_x, int p_y, int pwidth, int pheight)
    : x{std::move(p_x)}, y{std::move(p_y)}, width{std::move(pwidth)}, height{std::move(pheight)}
{
}
