//
// Created by kane on 04/01/24.
//

#pragma once

#include <nlohmann/json.hpp>

namespace rtype::utils
{
    /**
     * @brief Structure for 2 values, x and y. Values can be anything, as long as its consistent
     *
     * @tparam TComponent - template value
     */
    template <typename TComponent> struct Vector2D {
        public:
            TComponent x{0};
            TComponent y{0};
    };

    /**
     * @class TextureRect
     * @brief x, y, width and height values to have a rect. Is used for texture, hence its name
     *
     */
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
