//
// Created by kane on 14/12/23.
//

#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

#include <memory>
#include <rtype/SFML/SFMLGraphicModule.hh>

extern "C" {
std::unique_ptr<rtype::IGraphicModule> entrypoint(unsigned int width, unsigned int height,
                                                  const std::string &title)
{
    return std::make_unique<rtype::SFMLGraphicModule>(width, height, title);
}
}
