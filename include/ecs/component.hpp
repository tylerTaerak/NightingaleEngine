#pragma once

#include <cstddef>

namespace Nightingale::ECS {
    /**
     * @class Component
     *
     * This class serves as an interface for game components,
     * which are identifiers used by entities and systems to
     * classify how entities are interacted with in the game
     * as a whole.
     */
    class Component {
        public:
            Component(std::size_t typeId) 
                : m_typeId(typeId) {
            }

            std::size_t getTypeId() {
                return m_typeId;
            }

            virtual ~Component() = 0;
        private:
            std::size_t m_typeId;
    };

    inline Component::~Component() {}
}
