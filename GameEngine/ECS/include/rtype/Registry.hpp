//
// Created by kane on 28/11/23.
//

#pragma once

#include "Entity.hh"
#include "SparseArray.hpp"
#include <any>
#include <functional>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

class Registry
{
    public:
        Registry() = default;
        ~Registry() = default;
        Registry(const Registry &) = delete;
        Registry(Registry &&) = delete;
        Registry &operator=(const Registry &) = delete;
        Registry &operator=(Registry &&) = delete;

        template <class TComponent>
        constexpr SparseArray<TComponent> &register_component(SparseArray<TComponent> &array)
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                m_arrays[index] = std::any{array};
            return std::any_cast<SparseArray<TComponent> &>(m_arrays[index]);
        }

        template <class TComponent> constexpr SparseArray<TComponent> &get_components()
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                throw std::out_of_range("Not registered");
            return std::any_cast<SparseArray<TComponent> &>(m_arrays[index]);
        }

        template <class TComponent> constexpr SparseArray<TComponent> const &get_components() const
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                throw std::out_of_range("Not registered");
            const auto &res = std::any_cast<SparseArray<TComponent> &>(m_arrays[index]);
            return res;
        }

        template <class TComponent> std::type_index get_index() const
        {
            return std::type_index(typeid(TComponent));
        }

    private:
        std::unordered_map<std::type_index, std::any> m_arrays;
};
