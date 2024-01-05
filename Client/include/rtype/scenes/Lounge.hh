/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Lounge
*/

#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <rtype/GraphicModule.hh>
#include <rtype/components/Room.hh>
#include <rtype/utils/Clock.hh>
#include <rtype/utils/Vector2d.hpp>
#include <vector>

namespace rclient::scenes
{

    class Lounge
    {
        public:
            Lounge(const unsigned int &pwidth, const unsigned int &pheight);
            Lounge(Lounge const &to_copy) = default;
            Lounge(Lounge &&to_move) = default;
            ~Lounge() = default;
            Lounge &operator=(Lounge const &to_copy);
            Lounge &operator=(Lounge &&to_move);

            void manage_events(rtype::GraphicModule &graphics);
            void draw(rtype::GraphicModule &graphics, rtype::utils::Clock &clock);
            void add_room(unsigned int r_id);

        private:
            /* variables */
            sf::Font font{};
            sf::Sprite sprite{};
            sf::Text text{};
            unsigned int width{};
            unsigned int height{};

            /* scrollable */
            sf::View scrollable{};
            float end{};
            rtype::utils::Vector2d<float> global_pos{};
            std::vector<components::RoomInfos> rooms{};

            /* methods */
    };

} // namespace rclient::scenes
