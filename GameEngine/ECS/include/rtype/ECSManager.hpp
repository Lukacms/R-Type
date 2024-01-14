/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ECSManager
*/

#pragma once

#include <exception>
#include <rtype/ComponentManager.hpp>
#include <rtype/EntityManager.hh>
#include <rtype/SystemManager.hh>

#ifdef NDEBUG
    #define DEBUG(x)
#else
    #define DEBUG(x) printf x
#endif

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
                try {
                    return m_entity_manager.create_entity();
                } catch (EntityManager::EntityException &e) {
                    throw ECSManager::ECSException(e.what());
                }
            }

            Entity create_entity(std::size_t entity)
            {
                try {
                    return m_entity_manager.create_entity(entity);
                } catch (EntityManager::EntityException &e) {
                    throw ECSManager::ECSException(e.what());
                }
            }

            void delete_entity(size_t entity)
            {
                m_entity_manager.delete_entity(entity);
                m_component_manager.remove_all_component(entity);
            }

            template <class TComponent> void remove_component(size_t entity)
            {
                try {
                    m_component_manager.remove_component<TComponent>(entity);
                } catch (ComponentManager::ComponentException &e) {
                    throw ECSManager::ECSException(e.what());
                }
            }

            template <class TComponent>
            SparseArray<TComponent> &register_component(SparseArray<TComponent> &array)
            {
                return m_component_manager.register_component<TComponent>(array);
            }

            template <class TComponent> SparseArray<TComponent> &get_components()
            {
                try {
                    return m_component_manager.get_components<TComponent>();
                } catch (ComponentManager::ComponentException &e) {
                    throw ECSManager::ECSException(e.what());
                }
            }

            template <class TComponent> TComponent &get_component(size_t entity)
            {
                try {
                    SparseArray<TComponent> &components =
                        m_component_manager.get_components<TComponent>();
                    if (!components[entity].has_value())
                        throw ECSManager::ECSException("Component is not allocated\n");
                    return components[entity].value();
                } catch (ComponentManager::ComponentException &e) {
                    throw ECSManager::ECSException(e.what());
                }
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

            class ECSException : public std::exception
            {
                public:
                    ECSException(std::string &&perror) : error_msg{std::move(perror)}
                    {
                    }

                    ECSException(ECSException const &to_copy) = default;
                    ECSException(ECSException &&to_move) = default;
                    ~ECSException() override = default;
                    ECSException &operator=(ECSException const &to_copy) = default;
                    ECSException &operator=(ECSException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override
                    {
                        return this->error_msg.c_str();
                    }

                private:
                    std::string error_msg{};
            };

        private:
            ComponentManager m_component_manager{};
            SystemManager m_system_manager{};
            EntityManager m_entity_manager{};
    };
} // namespace rtype
