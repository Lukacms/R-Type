/*
** EPITECH PROJECT, 2023
** ECS2
** File description:
** SparseArray
*/

#pragma once

#include "ISparseArray.hh"
#include <exception>
#include <optional>
#include <vector>

template <typename TComponent> class SparseArray : public ISparseArray
{
    public:
        using value_type = std::optional<TComponent>;
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

        SparseArray() = default;
        SparseArray(SparseArray const &) = default;
        SparseArray(SparseArray &&) = default;
        SparseArray &operator=(SparseArray const &) = default;
        SparseArray &operator=(SparseArray &&) = default;
        ~SparseArray() override = default;

        reference_type operator[](size_t index)
        {
            return m_data[index];
        }

        const_reference_type operator[](size_t index) const
        {
            return m_data[index];
        }

        iterator begin()
        {
            return m_data.begin();
        }

        const_iterator begin() const
        {
            return m_data.begin();
        }

        const_iterator cbegin() const
        {
            return m_data.cbegin();
        }

        iterator end()
        {
            return m_data.end();
        }

        const_iterator end() const
        {
            return m_data.end();
        }

        const_iterator cend() const
        {
            return m_data.cend();
        }

        size_type size() const
        {
            return m_data.size();
        }

        reference_type insert_at(size_type pos, TComponent const &comp)
        {
            if (pos >= m_data.size())
                m_data.resize(pos + 1);
            m_data[pos] = comp;
            return m_data[pos];
        }

        reference_type insert_at(size_type pos, TComponent &&comp)
        {
            if (pos >= m_data.size())
                m_data.resize(pos + 1);
            m_data[pos] = comp;
            return m_data[pos];
        }

        template <class... TParams> reference_type emplace_at(size_type pos, TParams &&...args)
        {
            TComponent comps{args...};
            insert_at(pos, std::forward<TComponent>(comps));
            return m_data[pos];
        }

        void remove(size_t pos) override
        {
            if (pos > m_data.size())
                return;
            m_data[pos] = std::nullopt;
        }

        size_type get_index(value_type const &value) const
        {
            size_t index = 0;
            for (auto &data : m_data) {
                if (std::addressof(data) == std::addressof(value))
                    return index;
                index += 1;
            }
            return -1;
        }

    private:
        container_t m_data{};
};
