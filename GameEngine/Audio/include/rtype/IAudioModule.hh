//
// Created by kane on 04/01/24.
//

#pragma once

#include <string>

namespace rtype
{
    class IAudioModule
    {
        public:
            IAudioModule() = default;
            virtual ~IAudioModule() = default;
            IAudioModule(const IAudioModule &) = delete;
            IAudioModule(IAudioModule &&) = delete;
            IAudioModule &operator=(const IAudioModule &) = delete;
            IAudioModule &operator=(IAudioModule &&) = delete;

            virtual void play_music(const std::string &name) = 0;
            virtual void play_sfx(const std::string &name) = 0;
            virtual void set_volume_music(float volume) = 0;
            virtual void set_volume_sfx(float volume) = 0;
            virtual void update() = 0;
    };
} // namespace rtype
