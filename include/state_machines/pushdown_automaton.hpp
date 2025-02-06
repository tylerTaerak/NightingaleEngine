#pragma once

#include "fsm.hpp"
#include <stack>

namespace Nightingale::FSM {
    /**
     * @class PushdownAutomaton
     *
     * This class represents an advanced form
     * of a Finite State Machine, a Pushdown
     * Automaton. This class functions like an
     * FSM, but keeps a stack of states that
     * can be pushed to and popped from. This
     * allows greater flexibility when states
     * need to be revisited a lot.
     *
     * This class is the backbone behind the
     * Game's ability to switch between GameModes.
     */
    class PushdownAutomaton {
        public:
            /**
             * @brief ctor
             */
            PushdownAutomaton();

            /**
             * @brief ctor
             */
            PushdownAutomaton(std::map<std::size_t, std::shared_ptr<FsmState>> stateMap, std::size_t startingState);

            /**
             * @brief request_new_state
             *
             * Queues up a new state to transition to
             *
             * @param std::size_t stateId - id of the state to enqueue
             */
            void request_new_state(std::size_t stateId);

            /**
             * @brief get_current_state
             *
             * @returns FsmState * - a pointer to the current state
             */
            std::shared_ptr<FsmState> get_current_state();

            /**
             * @brief get_current_state_id
             *
             * @returns std::size_t - id of the current state
             */
            std::size_t get_current_state_id();

            /**
             * @brief return_to_previous_state
             *
             * Pops the top state off of the stack, queuing
             * the one below it to be the new one.
             */
            void return_to_previous_state();

            /**
             * @brief return_to_state
             *
             * Returns to a state anywhere in the state stack. If a state
             * was not in the stack, nothing will happen.
             *
             * @param std::size_t statdId - id of the state to return to
             *
             * @returns bool - true if state was returned to, false otherwise
             */
            bool return_to_state(std::size_t stateId);

            /**
             * @brief update
             *
             * Progresses the automaton one tick, processing
             * any changes of states.
             */
            void update();
        private:
            std::map<std::size_t, std::shared_ptr<FsmState>> m_stateMap;
            std::stack<std::size_t> m_stateStack;
            std::shared_ptr<FsmState> m_currentState;
    };
}
