#include <state_machines/fsm.hpp>

namespace Nightingale::FSM {
    FsmState::FsmState(std::size_t id)
        : m_id(id) {
        }

    std::size_t FsmState::get_id() {
        return m_id;
    }

    FSM::FSM(std::map<std::size_t, std::shared_ptr<FsmState>> stateMap, std::size_t startingState)
        : m_stateMap(stateMap),
        m_currentState(stateMap[startingState]),
        m_nextState(stateMap[startingState]) {
            m_currentState->on_enter();
        }

    void FSM::request_new_state(std::size_t stateId) {
        m_nextState = m_stateMap[stateId];
    }

    std::shared_ptr<FsmState> FSM::get_current_state() {
        return m_currentState;
    }

    std::size_t FSM::get_current_state_id() {
        return m_currentState->get_id();
    }

    void FSM::update() {
        if (m_currentState->get_id() != m_nextState->get_id()) {
            m_currentState->on_exit();
            m_currentState = m_nextState;
            m_currentState->on_enter();
        }
    }
}
