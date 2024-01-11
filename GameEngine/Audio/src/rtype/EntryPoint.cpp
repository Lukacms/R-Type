//
// Created by kane on 04/01/24.
//

#include <memory>
#include <rtype/SFML/SFMLAudioModule.hh>

#ifdef __linux

    #pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

extern "C" {
std::unique_ptr<rtype::IAudioModule> entrypoint()
{
    return std::make_unique<rtype::SFMLAudioModule>();
}
}

#else

extern "C" {
void *entrypoint()
{
    auto *audio{new rtype::SFMLAudioModule()};

    return static_cast<void *>(audio);
}
}

#endif /* __linux */
