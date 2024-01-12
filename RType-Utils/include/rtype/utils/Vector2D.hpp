//
// Created by kane on 04/01/24.
//

#pragma once

#include <nlohmann/json.hpp>

namespace rtype::utils
{
    template <typename TComponent> struct Vector2D {
        public:
            TComponent x{0};
            TComponent y{0};
    };

    struct TextureRect {
        public:
            int x{0};
            int y{0};
            int width{0};
            int height{0};

            TextureRect(int p_x = 0, int p_y = 0, int pwidth = 0, int pheight = 0);
            TextureRect(const TextureRect &to_copy) = default;
            TextureRect(TextureRect &&to_move) = default;
            TextureRect &operator=(const TextureRect &to_copy) = default;
            TextureRect &operator=(TextureRect &&to_move) = default;
            TextureRect(const nlohmann::json &json);
    };
} // namespace rtype::utils
