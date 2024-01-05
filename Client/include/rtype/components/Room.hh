/*
** EPITECH PROJECT, 2023
** components
** File description:
** Room
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <rtype/GraphicModule.hh>
#include <string>
#include <string_view>

namespace rclient::components
{

    constexpr std::string_view BASE_TITLE_ROOM{"Room "};

    class RoomInfos
    {
        public:
            RoomInfos(const unsigned int &pid);
            RoomInfos(RoomInfos const &to_copy) = default;
            RoomInfos(RoomInfos &&to_move) = default;
            ~RoomInfos() = default;
            RoomInfos &operator=(RoomInfos const &to_copy) = default;
            RoomInfos &operator=(RoomInfos &&to_move) = default;

            void display(rtype::GraphicModule &graphics, sf::Sprite &box);
            void set_nb_players(const unsigned int &new_players);

        private:
            std::string title{};
            unsigned int nb_players{1};
            unsigned int id;
            sf::Text text{};
    };

} // namespace rclient::components
