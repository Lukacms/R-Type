//
// Created by kane on 08/01/24.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/GameLogic/LevelManager/LevelManager.hh>

rserver::LevelManager::LevelManager()
{
    for (const auto &path : std::filesystem::directory_iterator(LEVEL_FOLDER.data())) {
        if (!path.is_regular_file())
            continue;
        if (path.path().extension() != ".json") {
            std::cerr << ERROR_LEVEL.data() << path.path().string() << "Not a JSON File"
                      << std::endl;
            continue;
        }
        std::ifstream level_file(path.path().string());
        if (!level_file.is_open())
            throw std::exception();
        auto level_json = nlohmann::json::parse(level_file);
        auto &new_level = this->m_levels.emplace_back();
        new_level.music = level_json["Music"];
        new_level.background = level_json["Background"];
        new_level.title = level_json["Title"];
        new_level.time = level_json["Timer"];
        for (const auto &wave : level_json["Waves"]) {
            auto &new_wave = new_level.waves.emplace_back();
            new_wave.time = wave["Timer"];
            new_wave.enemies = wave["Enemies"];
        }
    }
    if (!m_levels.empty())
        m_current_level = m_levels[static_cast<unsigned long>(std::rand()) % m_levels.size()].title;
}

void rserver::LevelManager::update(rtype::ECSManager &ecs_manager)
{
    for (auto &level : m_levels) {
        if (level.title != m_current_level)
            continue;
        manage_wave(level, ecs_manager);
    }
}

void rserver::LevelManager::manage_wave(rserver::Level &level, rtype::ECSManager &ecs_manager)
{
    for (auto &wave : level.waves) {
        if (m_level_clock.get_elapsed_time_in_ms() < wave.time || wave.is_done)
            continue;
        for (auto &enemy : wave.enemies) {
            std::size_t entity = rserver::ServerEntityFactory::create(enemy, ecs_manager);
            auto &transform = ecs_manager.get_component<rtype::TransformComponent>(entity);
            transform.position_y = std::rand() % 580;
            transform.velocity_x = -1.F * (static_cast<float>(std::rand() % 3) / 10) - 0.3F;
        }
        wave.is_done = true;
    }
}

bool rserver::LevelManager::has_enough_level()
{
    return !m_levels.empty();
}

bool rserver::LevelManager::is_level_finished()
{
    for (auto &level : m_levels) {
        if (m_current_level != level.title)
            continue;
        return level.time < m_level_clock.get_elapsed_time_in_ms();
    }
}

void rserver::LevelManager::change_level()
{
    std::size_t random_level = static_cast<unsigned long>(std::rand()) % m_levels.size();

    for (auto &level : m_levels) {
        if (level.title != m_current_level)
            continue;
        for (auto &wave : level.waves)
            wave.is_done = false;
    }
    m_current_level = m_levels[random_level].title;
    m_level_clock.reset();
}

std::string rserver::LevelManager::get_current_music()
{
    for (auto &level : m_levels) {
        if (level.title != m_current_level)
            continue;
        return level.music;
    }
    return "";
}
