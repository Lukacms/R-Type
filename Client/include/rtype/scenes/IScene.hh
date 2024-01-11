/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** IScene
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include <rtype/IAudioModule.hh>
#include <rtype/IGraphicModule.hh>
#include <rtype/network/Network.hpp>

namespace rclient::scenes
{

    constexpr int PLAY_FONT_SIZE{28};
    constexpr int LOGO_ORIGIN_X{250};
    constexpr float MIDLE_DIV{2.0F};
    constexpr float TEXT_HEIGHT_DIV{1.5F};
    constexpr float POS_Y_TEXT_MENU{50};
    constexpr double CLOCK_TIMER_LOGO{250};
    constexpr int LOGO_MAX_Y{60};
    constexpr int LOGO_MIN_Y{40};
    constexpr double CLOCK_TIMER_TEXT_MENU{50};
    constexpr int MAX_OPACITY_TEXT_MENU{250};
    constexpr int MIN_OPACITY_TEXT_MENU{50};
    constexpr int OPACITY_INCREMENTATION{5};
    constexpr float MENU_BG_WIDTH{1000.0F};
    constexpr float MENU_BG_HEIGHT{562.0F};
    // constexpr unsigned int STANDARD_WIDTH{800};
    // constexpr unsigned int STANDARD_HEIGHT{600};

    enum class State {
        Menu,
        Lounge,
        Game,
        Pause,
        End,
    };

    class IScene
    {
        public:
            IScene() = default;
            IScene(IScene const &to_copy) = default;
            IScene(IScene &&to_move) = default;
            virtual ~IScene() = default;
            IScene &operator=(IScene const &to_copy) = default;
            IScene &operator=(IScene &&to_move) = default;

            virtual void display(rtype::IGraphicModule &graphics) = 0;
            virtual void handle_events(rtype::IGraphicModule &graphics, rtype::IAudioModule &audio,
                                       State &state) = 0;
            virtual void handle_network(ntw::Communication &commn, rtype::IAudioModule &audio,
                                        State &state) = 0;
    };

} // namespace rclient::scenes
