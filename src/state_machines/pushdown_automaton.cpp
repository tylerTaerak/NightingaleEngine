#include "logger.hpp"
#include <cstddef>
#include <iostream>
#include <state_machines/pushdown_automaton.hpp>

namespace Nightingale::FSM {
    PushdownAutomaton::PushdownAutomaton()
        : m_currentState(NULL){
        }

    PushdownAutomaton::PushdownAutomaton(std::map<std::size_t, std::shared_ptr<FsmState>> stateMap, std::size_t startingState) 
        : m_stateMap(stateMap), m_stateStack(), m_currentState(stateMap[startingState]) {
            m_stateStack.emplace(startingState);
        }

    void PushdownAutomaton::request_new_state(std::size_t stateId) {
        LOG(NG_DEBUG, "Received new state request: " + std::to_string(stateId));
        m_stateStack.emplace(stateId);
    }

    std::shared_ptr<FsmState> PushdownAutomaton::get_current_state() {
        return m_currentState;
    }

    std::size_t PushdownAutomaton::get_current_state_id() {
        return m_currentState->get_id();
    }

    void PushdownAutomaton::return_to_previous_state() {
        m_stateStack.pop();
    }

    bool PushdownAutomaton::return_to_state(std::size_t stateId) {
        if (m_stateStack.empty()) {
            return false;
        }
        if (m_stateStack.top() == stateId) {
            return true;
        }
        
        std::size_t currentId = m_stateStack.top();

        m_stateStack.pop();

        bool stateFound = return_to_state(stateId);

        if (!stateFound) {
            m_stateStack.emplace(currentId);
        }

        return stateFound;
    }

    void PushdownAutomaton::update() {
        if (m_currentState == NULL || m_currentState->get_id() != m_stateStack.top()) {
            LOG(NG_DEBUG, "Switching Pushdown Automaton State");
            if (m_currentState != NULL) {
                m_currentState->on_exit();
            }

            m_currentState = m_stateMap[m_stateStack.top()];
            m_currentState->on_enter();
        }
    }
}
