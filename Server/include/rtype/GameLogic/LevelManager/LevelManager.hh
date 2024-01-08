//
// Created by kane on 08/01/24.
//

#pragma once

#include <rtype/utils/Clock.hh>
#include <vector>
#include <rtype/ECSManager.hpp>

namespace rserver {

    constexpr std::string_view LEVEL_FOLDER{"./Server/level/"};
    constexpr std::string_view ERROR_LEVEL{"R-Type : Enable to load the following level : "};

    struct Wave {
        double time;
        bool is_done{false};
        std::vector<std::string> enemies;
    };

    struct Level {
        std::string title;
        std::string background;
        std::string music;
        std::vector<Wave> waves;
    };

    class LevelManager {
        public:
            LevelManager();
            LevelManager(LevelManager const &to_copy) = delete;
            LevelManager(LevelManager &&to_move) = default;
            ~LevelManager() = default;
            LevelManager &operator=(LevelManager const &to_copy) = delete;
            LevelManager &operator=(LevelManager &&to_move) = delete;

            void update(rtype::ECSManager &ecs_manager);
            void manage_wave(Level &level, rtype::ECSManager &ecs_manager);
            bool has_enough_level();

        private:
            std::string m_current_level;
            rtype::utils::Clock m_level_clock;
            std::vector<Level> m_levels;
    };
}
