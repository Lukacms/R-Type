/*
** EPITECH PROJECT, 2024
** config
** File description:
** ConfigsFile
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <rtype.hh>
#include <rtype/config/ConfigsFile.hh>

/* static method */
/**
 * @brief static method to parse LEVEL_FOLDER file
 * @throws ConfigsException if something goes wrong
 */
std::vector<rserver::config::Level> rserver::config::ConfigsFile::parse()
{
    try {
        ConfigsFile config{};

        return config.do_parse();
    } catch (ConfigsException &e) {
        throw e;
    }
}

/**
 * @brief Method called by parse, to open and parse json file with nlohmann::json
 *
 * @return vector<Level>
 * @throws ConfigsException if something goes wrong
 */
std::vector<rserver::config::Level> rserver::config::ConfigsFile::do_parse()
{
    for (const auto &path : std::filesystem::directory_iterator(config::LEVEL_FOLDER.data())) {
        if (!path.is_regular_file())
            continue;
        if (path.path().extension() != ".json") {
            DEBUG(("%s%s%s%s", ERROR_LEVEL.data(), path.path().string().data(), " not a JSON File",
                   ENDL));
            continue;
        }
        std::ifstream level_file(path.path().string());
        if (!level_file.is_open())
            throw ConfigsException{};
        auto level_json = nlohmann::json::parse(level_file);
        auto &new_level = this->levels.emplace_back();
        new_level.music = level_json["Music"];
        new_level.background = level_json["Background"];
        new_level.title = level_json["Title"];
        new_level.time = level_json["Timer"];
        for (const auto &wave : level_json["Waves"]) {
            auto &new_wave = new_level.waves.emplace_back();
            new_wave.time = wave["Timer"];
            for (const auto &enemies : wave["Enemies"]) {
                this->add_enemies(enemies);
            }
        }
    }
    return this->levels;
}

/**
 * @brief Add enemies to level
 *
 * @param enemies - njson
 */
void rserver::config::ConfigsFile::add_enemies(const njson &enemies)
{
    std::string tag{enemies["tag"]};
    int numbers{enemies["nb"]};

    for (int i{0}; i < numbers; i++) {
        this->levels.back().waves.back().enemies.emplace_back(tag);
    }
}

/* exceptions */
rserver::config::ConfigsFile::ConfigsException::ConfigsException(std::string perror)
    : error{std::move(perror)}
{
}

const char *rserver::config::ConfigsFile::ConfigsException::what() const noexcept
{
    return this->error.c_str();
}
