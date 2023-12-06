//
// Created by kane on 06/12/23.
//

#pragma once

#include <rtype/EntityManager.hh>
#include <rtype/Registry.hpp>
#include <rtype/SystemManager.hh>

namespace rtype
{
    void movement_system(Registry &registry);
    void transform_system(Registry &registry);
    void sprite_system(Registry &registry);

    class ECSManager
    {
        public:
            ECSManager() = default;
            ECSManager(ECSManager const &to_copy) = default;
            ECSManager(ECSManager &&to_move) = default;
            ~ECSManager() = default;
            ECSManager &operator=(ECSManager const &to_copy) = default;
            ECSManager &operator=(ECSManager &&to_move) = default;

            Entity create_entity()
            {
                return m_entity_manager.create_entity();
            }

            void delete_entity(size_t entity)
            {
                m_entity_manager.delete_entity(entity);
            }

            template <class TComponent> void remove_component(size_t entity)
            {
                m_registry.remove_component<TComponent>(entity);
            }

            template <class TComponent>
            SparseArray<TComponent> &register_component(SparseArray<TComponent> &array)
            {
                return m_registry.register_component<TComponent>(array);
            }

            template <class TComponent> SparseArray<TComponent> &get_components()
            {
                return m_registry.get_components<TComponent>();
            }

            template <class TComponent> TComponent &get_component(size_t entity)
            {
                return m_registry.get_components<TComponent>()[entity].value();
            }

            std::function<void(Registry &)> &add_system(std::function<void(Registry &)> &function)
            {
                return m_system_manager.add_system(function);
            }

            void apply_system()
            {
                m_system_manager.update(m_registry);
            }

        private:
            Registry m_registry{};
            SystemManager m_system_manager{};
            EntityManager m_entity_manager{};
    };
} // namespace rtype
