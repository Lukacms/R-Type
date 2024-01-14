/*
** EPITECH PROJECT, 2023
** components
** File description:
** Room
*/

#pragma once

#include <array>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TextComponent.hh>
#include <rtype/IGraphicModule.hh>
#include <rtype/utils/Vector2D.hpp>
#include <string>
#include <string_view>

namespace rclient::components
{

    constexpr std::string_view BASE_TITLE_ROOM{"Room "};
    constexpr int TRANS_POS{40};
    static const sf::Vector2f ORIGIN_BOX{10, 50};
    constexpr int INFOS_SUBTITLE{20};
    constexpr int INFOS_TITLE{30};
    constexpr int POS1{35};
    constexpr int POS2{70};
    constexpr int POS3{40 * 9};
    constexpr int POS4{40 * 5};
    constexpr int POS5{20};

    /**
     * @class RoomInfos
     * @brief Infos about rooms, how to display them, ...
     *
     */
    class RoomInfos
    {
        public:
            RoomInfos(const unsigned int &pid, const std::string &font);
            RoomInfos(RoomInfos const &to_copy) = default;
            RoomInfos(RoomInfos &&to_move) = default;
            ~RoomInfos() = default;
            RoomInfos &operator=(RoomInfos const &to_copy) = default;
            RoomInfos &operator=(RoomInfos &&to_move) = default;

            void display(rtype::IGraphicModule &graphics, sf::Sprite &sprite,
                         rtype::TransformComponent &trans);
            void set_nb_players(const unsigned int &new_players);
            void set_status(const unsigned short &pstatus);
            [[nodiscard]] unsigned int get_id() const;
            [[nodiscard]] unsigned short get_status() const;
            [[nodiscard]] unsigned int get_nb_players() const;
            [[nodiscard]] sf::FloatRect get_box() const;

        private:
            std::string title{};
            unsigned int nb_players{1};
            unsigned int id;
            unsigned short status{0};
            rtype::TextComponent text{};
            sf::FloatRect box{};
            std::array<std::string, 3> statuses{"Lounge", "Waiting", "In Game"};
    };

} // namespace rclient::components
