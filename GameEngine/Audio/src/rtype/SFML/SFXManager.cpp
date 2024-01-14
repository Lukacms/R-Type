/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** SFXManager
*/

#include "rtype/SFML/SFXManager.hh"
#include "rtype/IAudioModule.hh"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

rtype::SFXManager::SFXManager()
{
    std::ifstream sfx_file(SFX_FILEPATH.data());

    if (!sfx_file.is_open())
        throw rtype::AudioModuleException("SFX Json file doesn't exist\n");
    auto sfx = nlohmann::json::parse(sfx_file);

    for (const auto &[key, value] : sfx.items()) {
        auto &buffer = m_buffers.emplace_back(key, sf::SoundBuffer{});
        buffer.sound_buffer.loadFromFile(static_cast<std::string>(value));
    }
}

void rtype::SFXManager::play_sound(const std::string &name)
{
    for (auto &sfx : m_buffers) {
        if (name != sfx.name)
            continue;
        auto &sound = m_sounds.emplace_back();
        sound.setBuffer(sfx.sound_buffer);
        sound.setVolume(m_volume);
        sound.play();
        return;
    }
    throw SFXException("SFX '" + name + "' doesn't exist\n");
}

void rtype::SFXManager::set_volume(float volume)
{
    if (volume >= 0 || volume < 100)
        m_volume = volume;
}

void rtype::SFXManager::update()
{
    for (auto iterator = m_sounds.cbegin(); iterator != m_sounds.cend(); iterator++) {
        if (iterator->getStatus() == sf::Sound::Stopped)
            iterator = m_sounds.erase(iterator);
    }
}

rtype::SFXManager::SFXException::SFXException(std::string &&perror_msg)
{
    m_error_msg = perror_msg;
}

const char *rtype::SFXManager::SFXException::what() const noexcept
{
    return m_error_msg.c_str();
}
