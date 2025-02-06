#pragma once

#include <ecs/entity.hpp>
#include <vector>
#include <utils/rwlock.hpp>

namespace Nightingale::ECS {
    /**
     * @class System
     *
     * This class is an interface, to be subclassed by specific systems.
     * It contains several utilities for interfacing with a system,
     * requiring any system to implement their own update method.
     *
     * Each system is intended to run on its own thread. The start()
     * method handles issuing each system to its own thread, and the
     * RwLock class handles read/write concurrency for game data.
     */
    class System {
        public:
            /**
             * @brief ctor
             */
            System(std::vector<std::size_t> componentTypes);

            virtual void update(const std::vector<std::shared_ptr<Utils::RwLock<Entity>>> &entities, float frameTime_ms) = 0;
        protected:
            /**
             * @brief is_interested
             *
             * @param size_t id - id of entity
             *
             * @returns bool - whether the system is interested in the entity
             */
            virtual bool is_interested(const Entity &entity);

        private:
            std::vector<std::size_t> m_components;
    };
}
