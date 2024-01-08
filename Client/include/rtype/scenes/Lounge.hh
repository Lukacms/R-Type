/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Lounge
*/

#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <rtype/SFML/SFMLGraphicModule.hh>
#include <rtype/components/Room.hh>
#include <rtype/scenes/IScene.hh>
#include <rtype/utils/Clock.hh>
#include <rtype/utils/Vector2d.hpp>
#include <vector>

namespace rclient::scenes
{

    class Lounge : public IScene
    {
        public:
            Lounge(const unsigned int &pwidth = rtype::STANDARD_WIDTH,
                   const unsigned int &pheight = rtype::STANDARD_HEIGHT);
            Lounge(Lounge const &to_copy) = default;
            Lounge(Lounge &&to_move) = default;
            ~Lounge() override = default;
            Lounge &operator=(Lounge const &to_copy);
            Lounge &operator=(Lounge &&to_move);

            void display(rtype::IGraphicModule &graphics) override;
            void handle_events(rtype::IGraphicModule &graphics, State &state) override;
            void add_room(unsigned int r_id);
            void handle_network(ntw::Communication &commn, State &state) override;

        private:
            /* variables */
            sf::Font font{};
            rtype::SpriteComponent sprite{};
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