//
// Created by kane on 04/01/24.
//

#include <fstream>
#include <rtype/IAudioModule.hh>
#include <rtype/SFML/BGMManager.hh>

rtype::BGMManager::BGMManager()
{
    std::ifstream bgm_file(BGM_FILEPATH.data());

    if (!bgm_file.is_open())
        throw rtype::AudioModuleException("BGM Json doesn't exist\n");
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
    if (m_current_name == name)
        return;
    for (auto &bgm : m_bgm) {
        if (bgm.name == name) {
            m_current_music.stop();
            if (!m_current_music.openFromFile(bgm.filepath))
                return;
            m_current_music.play();
            m_current_name = bgm.name;
            return;
        }
    }
    throw BGMException("BGM '" + name + "' doesn't exist\n");
}

rtype::BGMManager::BGMException::BGMException(std::string &&perror_msg)
{
    m_error_msg = perror_msg;
}

const char *rtype::BGMManager::BGMException::what() const noexcept
{
    return m_error_msg.c_str();
}
