/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Registry
*/

#pragma once

#include "Entity.hh"
#include "ISparseArray.hh"
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
                m_arrays[index] = std::move(std::make_unique<SparseArray<TComponent>>(array));
            return *static_cast<SparseArray<TComponent> *>(m_arrays[index].get());
        }

        template <class TComponent> SparseArray<TComponent> &get_components()
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                throw std::out_of_range("Not registered");
            return *static_cast<SparseArray<TComponent> *>(m_arrays[index].get());
        }

        template <class TComponent> SparseArray<TComponent> const &get_components() const
        {
            auto index = get_index<TComponent>();
            if (m_arrays.find(index) == m_arrays.end())
                throw std::out_of_range("Not registered");
            return *static_cast<const SparseArray<TComponent> *>(m_arrays[index].get());
        }

        template <class TComponent> void remove_component(size_t entity)
        {
            for (auto &val : m_arrays) {
                val.second->remove(entity);
            }
        }

        template <class TComponent> std::type_index get_index() const
        {
            return std::type_index(typeid(TComponent));
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<ISparseArray>> m_arrays;
};
