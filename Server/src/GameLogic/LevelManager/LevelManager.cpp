//
// Created by kane on 08/01/24.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <rtype.hh>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/GameLogic/LevelManager/LevelManager.hh>

rserver::LevelManager::LevelManager()
{
    try {
        m_levels = config::ConfigsFile::parse();
    } catch (config::ConfigsFile::ConfigsException &e) {
        DEBUG(("exception while loading levels, %s%s", e.what(), ENDL));
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

void rserver::LevelManager::manage_wave(config::Level &level, rtype::ECSManager &ecs_manager)
{
    for (auto &wave : level.waves) {
        if (m_level_clock.get_elapsed_time_in_ms() < wave.time || wave.is_done)
            continue;
        for (auto &enemy : wave.enemies) {
            try {
                std::size_t entity = rserver::ServerEntityFactory::create_json(enemy, ecs_manager);
                auto &transform = ecs_manager.get_component<rtype::TransformComponent>(entity);
                transform.position_y = std::rand() % WAVE_MODULO;
                transform.velocity_x = -1.F * (static_cast<float>(std::rand() % 3) / 10) - 0.3F;
            } catch (ServerEntityFactory::FactoryException & /* e */) {
            }
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
    return false;
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
