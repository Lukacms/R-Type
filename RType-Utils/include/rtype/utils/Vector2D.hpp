//
// Created by kane on 04/01/24.
//

#pragma once

namespace rtype::utils
{
    template <typename TComponent> struct Vector2D {
            TComponent x{0};
            TComponent y{0};
    };

    struct TextureRect {
            int x{0};
            int y{0};
            int width{0};
            int height{0};
    };
} // namespace rtype::utils
