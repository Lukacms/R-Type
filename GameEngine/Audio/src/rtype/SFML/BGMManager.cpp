//
// Created by kane on 04/01/24.
//

#include "rtype/SFML/BGMManager.hh"
#include <fstream>

rtype::BGMManager::BGMManager()
{
    std::ifstream bgm_file(BGM_FILEPATH.data());

    if (!bgm_file.is_open())
        throw std::exception();
    auto bgm = nlohmann::json::parse(bgm_file);

    for (const auto &[key, value] : bgm.items())
        m_bgm.emplace_back(key, static_cast<std::string>(value));
    m_current_music.setLoop(true);
}

rtype::BGMManager::~BGMManager()
{
    m_current_music.stop();
}

void rtype::BGMManager::update()
{
    m_current_music.setVolume(m_volume);
}

void rtype::BGMManager::set_volume(float volume)
{
    if (volume >= 0 && volume <= 100.F)
        m_volume = volume;
}

void rtype::BGMManager::play_music(const std::string &name)
{
    for (auto &bgm : m_bgm) {
        if (bgm.name == name) {
            m_current_music.stop();
            if (!m_current_music.openFromFile(bgm.filepath))
                return;
            m_current_music.play();
        }
    }
}
