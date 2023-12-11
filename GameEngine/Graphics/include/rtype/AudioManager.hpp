/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** audioManager
*/

#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class AudioManager {
private:
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;

public:
    AudioManager();
    ~AudioManager();

    bool loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    void setVolume(const std::string& name, float volume);
};

