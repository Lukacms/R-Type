/*
** EPITECH PROJECT, 2023
** components
** File description:
** Room
*/

#pragma once

#include <array>
#include <rtype/IGraphicModule.hh>
#include <string>
#include <string_view>

namespace rclient::components
{

    constexpr std::string_view BASE_TITLE_ROOM{"Room "};
    constexpr int TRANS_POS{40};

    class RoomInfos
    {
        public:
            RoomInfos(const unsigned int &pid, sf::Font &font);
            RoomInfos(RoomInfos const &to_copy) = default;
            RoomInfos(RoomInfos &&to_move) = default;
            ~RoomInfos() = default;
            RoomInfos &operator=(RoomInfos const &to_copy) = default;
            RoomInfos &operator=(RoomInfos &&to_move) = default;

            void display(rtype::IGraphicModule &graphics, sf::Sprite &box,
                         rtype::TransformComponent &trans);
            void set_nb_players(const unsigned int &new_players);
            void set_status(const unsigned short &pstatus);
            [[nodiscard]] unsigned int get_id() const;
            [[nodiscard]] unsigned short get_status() const;
            [[nodiscard]] unsigned int get_nb_players() const;

        private:
            std::string title{};
            unsigned int nb_players{1};
            unsigned int id;
            unsigned short status{0};
            sf::Text text{};
            std::array<std::string, 3> statuses{"Lounge", "Waiting", "In Game"};
    };

} // namespace rclient::components
