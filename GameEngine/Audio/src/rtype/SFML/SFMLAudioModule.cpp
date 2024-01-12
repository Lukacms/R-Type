//
// Created by kane on 04/01/24.
//

#include "rtype/SFML/SFMLAudioModule.hh"
#include <iostream>

void rtype::SFMLAudioModule::play_music(const std::string &name)
{
    try {
        m_bgm.play_music(name);
    } catch (rtype::BGMManager::BGMException &e) {
        std::cerr << e.what() << std::endl;
    }
}

void rtype::SFMLAudioModule::play_sfx(const std::string &name)
{
    try {
        m_sfx.play_sound(name);
    } catch (rtype::SFXManager::SFXException &e) {
        std::cerr << e.what() << std::endl;
    }
}

void rtype::SFMLAudioModule::set_volume_music(float volume)
{
    m_bgm.set_volume(volume);
}

void rtype::SFMLAudioModule::set_volume_sfx(float volume)
{
    m_bgm.set_volume(volume);
}

void rtype::SFMLAudioModule::update()
{
    m_bgm.update();
    m_sfx.update();
}
