//
// Created by kane on 04/01/24.
//

#include "rtype/SFML/SFMLAudioModule.hh"

void rtype::SFMLAudioModule::play_music(const std::string &name)
{
    m_bgm.play_music(name);
}

void rtype::SFMLAudioModule::play_sfx(const std::string &name)
{
    m_sfx.play_sound(name);
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
