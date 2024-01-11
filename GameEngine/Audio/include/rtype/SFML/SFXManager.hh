/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** SFXManager
*/

#pragma once

#include <SFML/Audio.hpp>
#include <list>
#include <nlohmann/json.hpp>
#include <string>

namespace rtype
{

    constexpr std::string_view SFX_FILEPATH{"./assets/configs/SFX.json"};
    constexpr float SFX_STANDARD_VOLUME{100.F};

    struct Buffer {
            std::string name;
            sf::SoundBuffer sound_buffer;
    };

    class SFXManager
    {
        public:
            SFXManager();
            ~SFXManager() = default;
            SFXManager(const SFXManager &) = default;
            SFXManager(SFXManager &&) = default;
            SFXManager &operator=(const SFXManager &) = default;
            SFXManager &operator=(SFXManager &&) = default;

            void play_sound(const std::string &name);
            void set_volume(float volume);
            void update();

        private:
            std::list<Buffer> m_buffers{};
            std::list<sf::Sound> m_sounds{};
            float m_volume{SFX_STANDARD_VOLUME};
    };
} // namespace rtype
