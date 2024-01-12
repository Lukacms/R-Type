//
// Created by kane on 08/01/24.
//

#pragma once

#include <rtype/ECSManager.hpp>
#include <rtype/config/ConfigsFile.hh>
#include <rtype/utils/Clock.hh>
#include <vector>

namespace rserver
{
    constexpr int WAVE_MODULO{580};

    class LevelManager
    {
        public:
            LevelManager();
            LevelManager(LevelManager const &to_copy) = delete;
            LevelManager(LevelManager &&to_move) = default;
            ~LevelManager() = default;
            LevelManager &operator=(LevelManager const &to_copy) = delete;
            LevelManager &operator=(LevelManager &&to_move) = delete;

            void update(rtype::ECSManager &ecs_manager);
            void manage_wave(config::Level &level, rtype::ECSManager &ecs_manager);
            bool has_enough_level();
            bool is_level_finished();
            void change_level();
            std::string get_current_music();
            std::string get_current_background();

        private:
            std::string m_current_level;
            rtype::utils::Clock m_level_clock;
            std::vector<config::Level> m_levels;
    };
} // namespace rserver
