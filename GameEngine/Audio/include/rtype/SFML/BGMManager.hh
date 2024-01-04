/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** BGMManager
*/

#pragma once

#include <SFML/Audio.hpp>
#include <list>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <memory>

namespace rtype
{

    constexpr std::string_view BGM_FILEPATH{"./Client/configs/BGM.json"};
    constexpr float BGM_STANDARD_VOLUME{25.F};

    struct BGM {
        std::string name{};
        std::string filepath{};
    };

    class BGMManager
    {
        public:
            BGMManager();
            ~BGMManager();
            BGMManager(const BGMManager &) = delete;
            BGMManager(BGMManager &&) = delete;
            BGMManager &operator=(const BGMManager &) = delete;
            BGMManager &operator=(BGMManager &&) = delete;

            void play_music(const std::string &name);
            void set_volume(float volume);
            void update();

        private:
            std::vector<BGM> m_bgm{};
            sf::Music m_current_music{};
            float m_volume{BGM_STANDARD_VOLUME};
    };
} // namespace rtype