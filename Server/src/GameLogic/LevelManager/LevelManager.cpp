/*
** EPITECH PROJECT, 2023
** LevelManager
** File description:
** LevelManager
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <rtype.hh>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/GameLogic/LevelManager/LevelManager.hh>

/**
 * @brief Constructor for LevelManager
 * Parse level files, and assign random level to be played
 */
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

/**
 * @brief Launch new vawes of enemies
 *
 * @param ecs_manager - ECSManager
 */
void rserver::LevelManager::update(rtype::ECSManager &ecs_manager)
{
    for (auto &level : m_levels) {
        if (level.title != m_current_level)
            continue;
        manage_wave(level, ecs_manager);
    }
}

/**
 * @brief Create all the entities of a wave of a level
 *
 * @param level - Level
 * @param ecs_manager - ECSManager
 */
void rserver::LevelManager::manage_wave(config::Level &level, rtype::ECSManager &ecs_manager)
{
    for (auto &wave : level.waves) {
        if (m_level_clock.get_elapsed_time_in_ms() < wave.time || wave.is_done)
            continue;
        for (auto &enemy : wave.enemies) {
            try {
                std::size_t entity = rserver::ServerEntityFactory::create(enemy, ecs_manager);
                auto &transform = ecs_manager.get_component<rtype::TransformComponent>(entity);
                transform.position_y = std::rand() % WAVE_MODULO;
                transform.velocity_x = -1.F * (static_cast<float>(std::rand() % 20) / 100) - 0.2F;
            } catch (ServerEntityFactory::FactoryException & /* e */) {
            }
        }
        wave.is_done = true;
    }
}

/**
 * @brief Check if there are at least one level
 *
 * @return bool
 */
bool rserver::LevelManager::has_enough_level()
{
    return !m_levels.empty();
}

/**
 * @brief Check if current playing level is finished, and has done all of its waves
 *
 * @return bool
 */
bool rserver::LevelManager::is_level_finished()
{
    for (auto &level : m_levels) {
        if (m_current_level != level.title)
            continue;
        return level.time < m_level_clock.get_elapsed_time_in_ms();
    }
    return false;
}

/**
 * @brief Change level, reset waves
 */
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

/**
 * @brief Get music depending on level
 *
 * @return string - path to the music
 */
std::string rserver::LevelManager::get_current_music()
{
    for (auto &level : m_levels) {
        if (level.title != m_current_level)
            continue;
        return level.music;
    }
    return "";
}

std::string rserver::LevelManager::get_current_background()
{
    for (auto &level : m_levels) {
        if (level.title != m_current_level)
            continue;
        return level.background;
    }
    return "";
}

void rserver::LevelManager::reset_clock()
{
    m_level_clock.reset();
}
