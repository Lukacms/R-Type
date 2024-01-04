/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Lounge
*/

#pragma once

#include "SFML/Window/Event.hpp"
#include "rtype/utils/Vector2d.hpp"
#include <SFML/Graphics/View.hpp>
#include <rtype/GraphicModule.hh>
#include <rtype/utils/Clock.hh>

namespace rclient
{

    class Lounge
    {
        public:
            Lounge(rtype::GraphicModule &pgraphics);
            Lounge(Lounge const &to_copy) = default;
            Lounge(Lounge &&to_move) = default;
            ~Lounge() = default;
            Lounge &operator=(Lounge const &to_copy);
            Lounge &operator=(Lounge &&to_move);

            void manage_events(sf::Event &events);
            void draw();

        private:
            /* variables */
            rtype::GraphicModule &graphics;
            rtype::utils::Clock clock{};
            sf::Font m_font{};
            sf::Sprite m_sprite{};
            sf::Text m_text{};
            unsigned int m_width{};
            unsigned int m_height{};

            /* scrollable */
            sf::View scrollable{};
            float end{};
            rtype::utils::Vector2d<float> global_pos{};

            /* methods */
    };

} // namespace rclient
