//
// Created by kane on 14/12/23.
//

#include <memory>
#include <rtype/SFML/SFMLGraphicModule.hh>

#ifdef __linux

#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

extern "C" {
std::unique_ptr<rtype::IGraphicModule> entrypoint(unsigned int width, unsigned int height,
                                                  const std::string &title)
{
    return std::make_unique<rtype::SFMLGraphicModule>(width, height, title);
}
}

#else

extern "C" {
void * entrypoint(unsigned int width, unsigned int height,
                                                  const std::string &title)
{
    auto *sfml{new rtype::SFMLGraphicModule(width, height, title)};

    return static_cast<void *>(sfml);
}
}

#endif /* __linux */