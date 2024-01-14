//
// Created by kane on 04/01/24.
//

#pragma once

#include "BGMManager.hh"
#include "SFML/Audio.hpp"
#include "SFXManager.hh"
#include "rtype/IAudioModule.hh"
#include <list>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace rtype
{
    class SFMLAudioModule : public IAudioModule
    {
        public:
            SFMLAudioModule() = default;
            ~SFMLAudioModule() override = default;
            SFMLAudioModule(const SFMLAudioModule &) = delete;
            SFMLAudioModule(SFMLAudioModule &&) = delete;
            SFMLAudioModule &operator=(const SFMLAudioModule &) = delete;
            SFMLAudioModule &operator=(SFMLAudioModule &&) = delete;

            void play_music(const std::string &name) final;
            void play_sfx(const std::string &name) final;
            void set_volume_music(float volume) final;
            void set_volume_sfx(float volume) final;
            void update() final;

        private:
            rtype::SFXManager m_sfx;
            rtype::BGMManager m_bgm;
    };
} // namespace rtype
