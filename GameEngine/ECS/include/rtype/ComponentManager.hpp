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

class ComponentManager
{
    public:
        ComponentManager() = default;
        ~ComponentManager() = default;
        ComponentManager(const ComponentManager &) = default;
        ComponentManager(ComponentManager &&) = default;
        ComponentManager &operator=(const ComponentManager &) = default;
        ComponentManager &operator=(ComponentManager &&) = default;

        template <class TComponent>
        SparseArray<TComponent> &register_component(SparseArray<TComponent> &array)
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                m_arrays[index] = std::any{array};
            return std::any_cast<SparseArray<TComponent> &>(m_arrays[index]);
        }

        template <class TComponent> SparseArray<TComponent> &get_components()
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                throw std::out_of_range("Not registered");
            return std::any_cast<SparseArray<TComponent> &>(m_arrays[index]);
        }

        template <class TComponent> SparseArray<TComponent> const &get_components() const
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                throw std::out_of_range("Not registered");
            const auto &res = std::any_cast<SparseArray<TComponent> &>(m_arrays[index]);
            return res;
        }

        template <class TComponent> void remove_component(size_t entity)
        {
            auto index = get_index<TComponent>(entity);
            if (m_arrays.find(index) == m_arrays.end())
                throw std::out_of_range("Not registered");
            auto &res = std::any_cast<SparseArray<TComponent> &>(m_arrays[index]);
            res[entity] = std::nullopt;
        }

        template <class TComponent> std::type_index get_index() const
        {
            return std::type_index(typeid(TComponent));
        }

    private:
        std::unordered_map<std::type_index, std::any> m_arrays;
};
