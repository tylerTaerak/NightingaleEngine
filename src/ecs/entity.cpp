#include "logger.hpp"
#include <ecs/component.hpp>
#include <ecs/entity.hpp>
#include <string>

namespace Nightingale::ECS {
    size_t Entity::s_idCount = 0;

    void Entity::add_component(const std::shared_ptr<Component>& component) {
        auto iter = m_components.find(component->getTypeId());

        if (iter != m_components.end()) {
            LOG(NG_INFO, "A Component of ID: " + std::to_string(component->getTypeId()) + " is already in Entity " + std::to_string(m_id));
            return;
        }

        m_components.emplace(component->getTypeId(), component);
    }

    std::shared_ptr<Component> Entity::get_component(std::size_t typeId) const {
        auto iter = m_components.find(typeId);

        if (iter != m_components.end()) {
            return iter->second;
        }

        LOG(NG_WARN, "Component type: " + std::to_string(typeId) + " not found, returning nullptr");
        return nullptr;
    }

    bool Entity::contains_component(std::size_t typeId) const {
        return m_components.find(typeId) != m_components.end();
    }

    size_t Entity::get_id() const {
        return m_id;
    }
}
