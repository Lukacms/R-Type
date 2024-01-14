/*
** EPITECH PROJECT, 2023
** utils
** File description:
** Colors
*/

#include <rtype/utils/Color.hh>

/**
 * @namespace rtype::utils
 * @brief define enums of basic colors to not be obligated to define them each time
 * Should be noted that it does not seems to works on windows
 */
namespace rtype::utils
{
    const Colors Colors::Black{0, 0, 0};
    const Colors Colors::White{255, 255, 255};
    const Colors Colors::Red{255, 0, 0};
    const Colors Colors::Green{0, 0, 255};
    const Colors Colors::Blue{0, 0, 255};

} // namespace rtype::utils
