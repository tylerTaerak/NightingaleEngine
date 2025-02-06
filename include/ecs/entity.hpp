#pragma once

#include "component.hpp"
#include <map>
#include <cstddef>
#include <memory>
#include <utils/logger.hpp>

namespace Nightingale::ECS {
    /**
     * @class Entity
     *
     * An entity is a game object. It is composed of Component objects,
     * and has several utilities for accessing the information of those
     * components.
     */
    class Entity final {
        public:
            /**
             * @brief ctor
             */
            Entity()
                : m_id(s_idCount++) {
                }

            /**
             * @brief dtor
             *
             * Clears the component map and frees the memory of stored components
             */
            ~Entity() {
                m_components.clear();
            }

            /**
             * @brief add_component
             *
             * Adds a component to the component map, using component->id as its key
             *
             * @param Component *component - component to be added to the Entity
             */
            void add_component(const std::shared_ptr<Component>& component);

            /**
             * @brief get_component
             *
             * @param std::size_t typeId - typeId of the component to be queried
             *
             * @returns Component * - pointer to the request component (can be nullptr)
             */
            std::shared_ptr<Component> get_component(std::size_t typeId) const;

            /**
             * @brief contains_component
             *
             * @param std::size_t typeId - typeId of the component to be queried
             *
             * @returns bool - true if component type is present in component map, false otherwise
             */
            bool contains_component(std::size_t typeId) const;

            /**
             * @brief get_id
             *
             * @returns size_t - the id of this entity
             */
            size_t get_id() const;

        private:
            size_t m_id;
            std::map<std::size_t, std::shared_ptr<Component>> m_components;

            static size_t s_idCount;
    };
}
