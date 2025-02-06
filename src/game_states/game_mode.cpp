#include <game_states/game_mode.hpp>
#include "utils/logger.hpp"

namespace Nightingale::GameStates {
    GameMode::GameMode(std::size_t id)
        : FSM::FsmState(id), m_front(0), m_back(0) {
        }

    std::size_t GameMode::init_entity() {
        ECS::Entity *currEnt = m_entities[m_back].read().get_data();

        m_indexMap.emplace(currEnt->get_id(), m_back++);

        return currEnt->get_id();
    }

    Utils::RwLock<ECS::Entity> &GameMode::get_entity(std::size_t id) {
        auto it = m_indexMap.find(id);

        if (it == m_indexMap.end()) {
            LOG(NG_FATAL, "Could not retrieve entity with id: " + std::to_string(id));
        }

        return m_entities[it->second];
    }

    void GameMode::remove_entity(std::size_t id) {
        m_indexMap.erase(id);
    }

    void GameMode::add_system(ECS::System &system) {
        m_systems.push_back(&system);
    }

    void GameMode::add_system(ECS::RenderSystem &system) {
        m_systems.push_back(&system);
        m_renderSystems.push_back(&system);
    }

    void GameMode::update(float frameTime) {
        std::vector<std::shared_ptr<Utils::RwLock<ECS::Entity>>> activeEntities;
        for (auto &pair : m_indexMap) {
            activeEntities.push_back(std::shared_ptr<Utils::RwLock<ECS::Entity>>(&m_entities[pair.second]));
        }

        for (ECS::System *&system : m_systems) {
            system->update(activeEntities, frameTime);
        }
    }

    void GameMode::draw() {
        for (ECS::RenderSystem *&system : m_renderSystems) {
            system->draw();
        }
    }
}
