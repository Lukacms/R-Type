/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Registry
*/

#pragma once

#include <any>
#include <exception>
#include <functional>
#include <rtype/Entity.hh>
#include <rtype/ISparseArray.hh>
#include <rtype/SparseArray.hpp>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

namespace rtype
{
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
                    throw ComponentException("Not registered");
                return *static_cast<SparseArray<TComponent> *>(m_arrays[index].get());
            }

            template <class TComponent> SparseArray<TComponent> const &get_components() const
            {
                auto index = get_index<TComponent>();
                if (m_arrays.find(index) == m_arrays.end())
                    throw ComponentException("Not registered");
                return *static_cast<const SparseArray<TComponent> *>(m_arrays[index].get());
            }

            template <class TComponent> void remove_component(size_t entity)
            {
                auto index = get_index<TComponent>();
                if (m_arrays.find(index) == m_arrays.end())
                    throw ComponentException("Not registered");
                m_arrays[index]->remove(entity);
            }

            void remove_all_component(size_t entity)
            {
                for (auto &val : m_arrays)
                    val.second->remove(entity);
            }

            template <class TComponent> std::type_index get_index() const
            {
                return std::type_index(typeid(TComponent));
            }

            class ComponentException : public std::exception
            {
                public:
                    ComponentException(std::string &&perror) : error_msg{std::move(perror)}
                    {
                    }

                    ComponentException(ComponentException const &to_copy) = default;
                    ComponentException(ComponentException &&to_move) = default;
                    ~ComponentException() override = default;
                    ComponentException &operator=(ComponentException const &to_copy) = default;
                    ComponentException &operator=(ComponentException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override
                    {
                        return this->error_msg.c_str();
                    }

                private:
                    std::string error_msg;
            };

        private:
            std::unordered_map<std::type_index, std::unique_ptr<ISparseArray>> m_arrays{};
    };

} // namespace rtype
