/*
** EPITECH PROJECT, 2023
** utils
** File description:
** Color
*/

#pragma once

namespace rtype::utils
{
    constexpr int MAX_COLOR{255};

    struct Colors {
        public:
            unsigned char red{0};
            unsigned char green{0};
            unsigned char blue{0};
            unsigned char opacity{MAX_COLOR};

            static const Colors Black; // NOLINT
            static const Colors White; // NOLINT
            static const Colors Red;   // NOLINT
            static const Colors Green; // NOLINT
            static const Colors Blue;  // NOLINT
    };

} // namespace rtype::utils
