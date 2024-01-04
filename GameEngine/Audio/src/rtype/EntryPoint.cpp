//
// Created by kane on 04/01/24.
//

#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

#include <rtype/SFML/SFMLAudioModule.hh>
#include <memory>

extern "C" {
std::unique_ptr<rtype::IAudioModule> entrypoint()
{
    return std::make_unique<rtype::SFMLAudioModule>();
}
}
