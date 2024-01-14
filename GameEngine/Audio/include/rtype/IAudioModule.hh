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

    class AudioModuleException : std::exception
    {
        public:
            AudioModuleException(std::string &&perror_msg);
            AudioModuleException(AudioModuleException const &to_copy) = default;
            AudioModuleException(AudioModuleException &&to_move) = default;
            ~AudioModuleException() override = default;
            AudioModuleException &operator=(AudioModuleException const &to_copy) = default;
            AudioModuleException &operator=(AudioModuleException &&to_move) = default;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string m_error_msg{"Error"};
    };

} // namespace rtype
