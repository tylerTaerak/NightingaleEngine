#pragma once

#include "ecs/entity.hpp"
#include "utils/rwlock.hpp"
#include <vector>
#include <state_machines/fsm.hpp>
#include <ecs/system.hpp>
#include <ecs/render_system.hpp>

#define MAX_ENTITIES 10000

namespace Nightingale::GameStates {
    /**
     * @class GameMode
     *
     * This class represents a mode of gameplay,
     * such as a level, a menu, etc. The Game class
     * uses GameMode objects to switch between
     * these modes of play.
     */
    class GameMode : public FSM::FsmState {
        public:
            /**
             * @brief ctor
             */
            GameMode(std::size_t id);

            /**
             * @brief add_entity
             *
             * @param Entity entity - entity to be added
             *
             * adds an entity to this game mode
             */
            std::size_t init_entity();

            /**
             * @brief get_entity
             *
             * @param std::size_t id - id of entity to be retrieved
             *
             * @return RwLock<ECS::Entity> - read-write lock containing the requested entity
             */
            Utils::RwLock<ECS::Entity> &get_entity(std::size_t id);

            /**
             * @brief remove_entity
             *
             * @param std::size_t id - id of entity to be removed
             *
             * removes an entity from the game mode (it only removes the entity from
             * the index map, rather than freeing up any memory)
             */
            void remove_entity(std::size_t id);

            /**
             * @brief add_system
             *
             * @param System system - system to be added
             */
            void add_system(ECS::System &system);

            /**
             * @brief add_system
             *
             * @param RenderSystem system - a RenderSystem to be added
             */
            void add_system(ECS::RenderSystem &system);

            /**
             * @brief update
             *
             * @param float frameTime - last elapsed frame time
             */
            void update(float frameTime);

            /**
             * @brief draw
             *
             * Calls the draw() method of all RenderSystems
             */
            void draw();

            virtual void on_enter() = 0;

            virtual void on_exit() = 0;
        private:
            std::vector<ECS::System *> m_systems;
            std::vector<ECS::RenderSystem *> m_renderSystems;
            Utils::RwLock<ECS::Entity> m_entities[MAX_ENTITIES];
            std::map<std::size_t, std::size_t> m_indexMap;

            std::size_t m_front;
            std::size_t m_back;
    };
}
