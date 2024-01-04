//
// Created by kane on 04/01/24.
//

#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

#include <memory>
#include <rtype/SFML/SFMLAudioModule.hh>

extern "C" {
std::unique_ptr<rtype::IAudioModule> entrypoint()
{
    return std::make_unique<rtype::SFMLAudioModule>();
}
}
