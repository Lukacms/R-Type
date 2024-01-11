//
// Created by kane on 11/01/24.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <nlohmann/json.hpp>
#include <string>

using njson = nlohmann::json;

namespace rtype
{

    constexpr std::string_view TEXTURE_LIBRARY_PATH{"./assets/configs/Texture.json"};

    struct TextureBook {
            std::string name;
            sf::Texture texture;
    };

    class TextureLibrary
    {
        public:
            TextureLibrary();
            ~TextureLibrary() = default;
            TextureLibrary(const TextureLibrary &) = default;
            TextureLibrary(TextureLibrary &&) = default;
            TextureLibrary &operator=(const TextureLibrary &) = default;
            TextureLibrary &operator=(TextureLibrary &&) = default;

            TextureBook &get_texture(std::string &name);

        private:
            std::list<TextureBook> m_library;
    };
} // namespace rtype
