#include <ecs/system.hpp>

namespace Nightingale::ECS {
    System::System(std::vector<std::size_t> componentTypes)
        : m_components({componentTypes}) {
        }

    bool System::is_interested(const Entity &entity) {
        for (std::size_t type : m_components) {
            if (!entity.contains_component(type)) {
                return false;
            }
        }

        return true;
    }
}
