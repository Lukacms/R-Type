//
// Created by kane on 11/01/24.
//

#include <fstream>
#include <iostream>
#include <rtype/SFML/TextureLibrary.hh>

rtype::TextureLibrary::TextureLibrary()
{
    std::ifstream texture_file(TEXTURE_LIBRARY_PATH.data());

    if (!texture_file.is_open()) {
        std::cerr << "Cannot load textures because texture file doesn't exist" << std::endl;
        throw std::exception();
    }
    auto textures = njson::parse(texture_file);

    for (const auto &[key, value] : textures.items()) {
        auto &new_texture = m_library.emplace_back();
        new_texture.name = key;
        new_texture.texture.loadFromFile(static_cast<std::string>(value));
    }
}

rtype::TextureBook &rtype::TextureLibrary::get_texture(std::string &name)
{
    for (auto &texture : m_library) {
        if (name == texture.name)
            return texture;
    }
    throw std::exception();
}
