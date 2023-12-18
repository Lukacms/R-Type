/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** audioManager
*/

#include <rtype/AudioManager.hpp>

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
    for (auto &sound : sounds) {
        sound.second.stop();
    }
}

bool AudioManager::loadSound(const std::string &name, const std::string &filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        return false;
    }

    soundBuffers[name] = buffer;
    sounds[name].setBuffer(soundBuffers[name]);
    return true;
}

void AudioManager::playSound(const std::string &name)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.play();
    }
}

void AudioManager::stopSound(const std::string &name)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.stop();
    }
}

void AudioManager::setVolume(const std::string &name, float volume)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.setVolume(volume);
    }
}