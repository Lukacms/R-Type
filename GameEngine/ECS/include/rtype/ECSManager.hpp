//
// Created by kane on 06/12/23.
//

#pragma once

#include <rtype/ComponentManager.hpp>
#include <rtype/EntityManager.hh>
#include <rtype/SystemManager.hh>

namespace rtype
{
    void movement_system(ComponentManager &registry, float);
    void transform_system(ComponentManager &registry, float);
    void sprite_system(ComponentManager &registry, float);
    void collider_system(ComponentManager &registry, [[maybe_unused]] float delta_time);

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

            Entity create_entity(std::size_t entity)
            {
                return m_entity_manager.create_entity(entity);
            }

            void delete_entity(size_t entity)
            {
                m_entity_manager.delete_entity(entity);
                m_component_manager.remove_all_component(entity);
            }

            template <class TComponent> void remove_component(size_t entity)
            {
                m_component_manager.remove_component<TComponent>(entity);
            }

            template <class TComponent>
            SparseArray<TComponent> &register_component(SparseArray<TComponent> &array)
            {
                return m_component_manager.register_component<TComponent>(array);
            }

            template <class TComponent> SparseArray<TComponent> &get_components()
            {
                return m_component_manager.get_components<TComponent>();
            }

            template <class TComponent> TComponent &get_component(size_t entity)
            {
                return m_component_manager.get_components<TComponent>()[entity].value();
            }

            std::function<void(ComponentManager &, float)> &
            add_system(std::function<void(ComponentManager &, float)> &function)
            {
                return m_system_manager.add_system(function);
            }

            void apply_system(float delta_time)
            {
                m_system_manager.update(m_component_manager, delta_time);
            }

            bool is_entity_used(std::size_t entity)
            {
                return m_entity_manager.is_entity_used(entity);
            }

            std::vector<std::size_t> get_used_entity()
            {
                return m_entity_manager.get_used_entity();
            }

        private:
            ComponentManager m_component_manager{};
            SystemManager m_system_manager{};
            EntityManager m_entity_manager{};
    };
} // namespace rtype
