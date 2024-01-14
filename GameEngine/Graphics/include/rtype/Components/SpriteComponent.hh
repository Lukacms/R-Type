/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite_component
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <rtype/utils/Vector2D.hpp>
#include <string>

namespace rtype
{

    struct SpriteComponent {
        public:
            rtype::utils::TextureRect rectangle{};
            std::string texture_path{};
            rtype::utils::Vector2D<float> origin{};
            int opacity{255};

            SpriteComponent(rtype::utils::TextureRect prec = {}, std::string text = "",
                            rtype::utils::Vector2D<float> pog = {});
            SpriteComponent(SpriteComponent const &to_copy) = default;
            SpriteComponent(SpriteComponent &&to_move) = default;
            ~SpriteComponent() = default;
            SpriteComponent &operator=(SpriteComponent const &to_copy) = default;
            SpriteComponent &operator=(SpriteComponent &&to_move) = default;
            /* njson */
            SpriteComponent(const nlohmann::json &json);
    };
} // namespace rtype
