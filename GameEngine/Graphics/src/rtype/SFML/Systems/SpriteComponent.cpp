/*
** EPITECH PROJECT, 2023
** Systems
** File description:
** SpriteComponent
*/

#include <rtype/SFML/SFMLGraphicModule.hh>

rtype::SpriteComponent::SpriteComponent(rtype::utils::TextureRect prec, std::string text,
                                        rtype::utils::Vector2D<float> pog)
    : rectangle{std::move(prec)}, texture_path{std::move(text)}, origin{std::move(pog)}
{
}

rtype::SpriteComponent::SpriteComponent(const nlohmann::json &json)
{
    if (!json["origin"].is_null())
        this->origin = {json["origin"]["x"], json["origin"]["y"]};
    if (!json["textureRect"].is_null())
        this->rectangle = {json["textureRect"]["x"], json["textureRect"]["y"],
                           json["textureRect"]["width"], json["textureRect"]["height"]};
    this->texture_path = json["texturePath"];
}
