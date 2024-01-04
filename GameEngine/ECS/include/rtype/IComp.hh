/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** IComp
*/

#pragma once

namespace rtype
{

    class IComp // base de mon comp tout mes comps en hérite
    {
        public:
            IComp() = default;
            IComp(IComp const &to_copy) = default;
            IComp(IComp &&to_move) = default;
            virtual ~IComp() = default;
            IComp &operator=(IComp const &to_copy) = default;
            IComp &operator=(IComp &&to_move) = default;
    };

} // namespace rtype
