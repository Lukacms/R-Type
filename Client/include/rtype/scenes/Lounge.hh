/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Lounge
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the client core
#define ASIO_HEADER_ONLY

#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <asio.hpp>
#include <rtype/IAudioModule.hh>
#include <rtype/IGraphicModule.hh>
#include <rtype/SFML/SFMLGraphicModule.hh>
#include <rtype/components/Room.hh>
#include <rtype/scenes/IScene.hh>
#include <rtype/utils/Clock.hh>
#include <rtype/utils/Vector2D.hpp>
#include <string_view>
#include <vector>

namespace rclient::scenes
{

    constexpr std::string_view NEW_ROOM{"NEW ROOM"};
    constexpr std::string_view JOIN_ROOM{"JOIN ROOM"};
    constexpr std::string_view FONT_FILE{"./assets/font.ttf"};
    constexpr std::string_view ROOM_CONTAINER{"./assets/Room.png"};
    static const sf::FloatRect VIEWPORT{0.25F, 0.05F, 0.6F, 0.6F};
    constexpr int CHANGE_SCROLL{5};
    constexpr int TEXT_POS_LOUNGE{100};
    constexpr int ROOM_TIMEOUT{200};

    class Lounge : public IScene
    {
        public:
            Lounge(asio::ip::udp::socket &psocket, asio::ip::udp::endpoint &pendpoint,
                   const unsigned int &pwidth = rtype::STANDARD_WIDTH,
                   const unsigned int &pheight = rtype::STANDARD_HEIGHT);
            Lounge(Lounge const &to_copy) = default;
            Lounge(Lounge &&to_move) = default;
            ~Lounge() override = default;
            Lounge &operator=(Lounge const &to_copy) = delete;
            Lounge &operator=(Lounge &&to_move) = delete;

            void display(rtype::IGraphicModule &graphics) override;
            void add_room(unsigned int r_id);
            void handle_events(rtype::IGraphicModule &graphics, rtype::IAudioModule &audio,
                               State &state) override;
            void handle_network(ntw::Communication &commn, rtype::IAudioModule &audio,
                                State &state) override;

            /* function pointers for network */
            void rooms_handler(std::vector<std::string> &args, State &state);
            void end_handler(std::vector<std::string> &args, State &state);
            void to_game_handler(std::vector<std::string> &args, State &state);

        private:
            /* variables */
            sf::Font font{};
            sf::Texture texture{};
            sf::Sprite sprite{};
            sf::Text text{};
            sf::FloatRect new_box{};
            sf::FloatRect join_box{};
            unsigned int width{};
            unsigned int height{};
            std::array<std::string, 1> paths{"./assets/SpaceBG.png"};
            std::array<rtype::TransformComponent, 2> transforms{};
            rtype::utils::Clock new_room{};

            /* scrollable */
            sf::View scrollable{};
            float end{};
            rtype::utils::Vector2D<float> global_pos{0, 0};
            std::vector<components::RoomInfos> rooms{};

            /* network */
            asio::ip::udp::endpoint &endpoint;
            asio::ip::udp::socket &socket;
    };

    struct LoungeNtwHandler {
        public:
            ntw::NetworkType type;
            std::function<void(Lounge &, std::vector<std::string> &, State &)> handler;
    };

} // namespace rclient::scenes
