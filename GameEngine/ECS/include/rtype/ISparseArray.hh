/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ISparseArray
*/

#pragma once

#include "IComp.hh"
#include <memory>

class ISparseArray
{
    public:
        ISparseArray() = default;
        ISparseArray(ISparseArray const &to_copy) = default;
        ISparseArray(ISparseArray &&to_move) = default;
        virtual ~ISparseArray() = default;
        ISparseArray &operator=(ISparseArray const &to_copy) = default;
        ISparseArray &operator=(ISparseArray &&to_move) = default;

        virtual void remove(size_t entity) = 0;
        //        [[nodiscard]] virtual std::unique_ptr<IComp> get_component(size_t id) = 0;
};
