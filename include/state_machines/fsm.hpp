#pragma once

#include <map>
#include <memory>

namespace Nightingale::FSM {
    /**
     * @class FsmState
     *
     * This class represents a single element
     * in a Finite State Machine or Pushdown
     * Automaton. It is initialized with an
     * id. These ids work best when mapped
     * to enum values for code clarity.
     */
    class FsmState {
        public:
            /**
             * @brief ctor
             */
            FsmState(std::size_t id);

            /**
             * @brief get_id
             *
             * @returns std::size_t - the id of this state
             */
            std::size_t get_id();

            virtual void on_enter() = 0;

            virtual void on_exit() = 0;
        private:
            std::size_t m_id;
    };

    /**
     * @class FSM
     *
     * This class is the Finite State Machine,
     * which handles the transitions between
     * multiple different dynamic states.
     */
    class FSM {
        public:
            /**
             * @brief ctor
             */
            FSM(std::map<std::size_t, std::shared_ptr<FsmState>> stateMap, std::size_t startingState);

            /**
             * @brief request_new_state
             *
             * Queues up a state to transition to
             *
             * @param std::size_t stateId - the id of the state which is being requested
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
             * @returns std::size_t - the id of the current state
             */
            std::size_t get_current_state_id();

            /**
             * @brief update
             *
             * updates the state machine one tick, handling transitions
             * between states
             */
            void update();
        private:
            std::map<std::size_t, std::shared_ptr<FsmState>> m_stateMap;
            std::shared_ptr<FsmState> m_currentState;
            std::shared_ptr<FsmState> m_nextState;
    };
}
