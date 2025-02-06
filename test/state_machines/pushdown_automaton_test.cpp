#include "state_machines/fsm.hpp"
#include <state_machines/pushdown_automaton.hpp>
#include <gtest/gtest.h>

TEST(PushdownAutomatonTests, CreatePushdownAutomaton) {
    class MyState : public Nightingale::FSM::FsmState {
        public:
            MyState(size_t id)
                : FsmState(id) {
            }

            void on_enter() {
            }

            void on_exit() {
            }
    };

    std::shared_ptr<MyState> state = std::make_shared<MyState>(0);

    std::map<std::size_t, std::shared_ptr<Nightingale::FSM::FsmState>> map;

    map.emplace(state->get_id(), state);

    Nightingale::FSM::PushdownAutomaton pa(map, state->get_id());

    ASSERT_TRUE(true);
}

TEST(PushdownAutomatonTests, SwitchStatesBackAndForth) {
    class MyState : public Nightingale::FSM::FsmState {
        public:
            MyState(size_t id)
                : FsmState(id) {
            }

            void on_enter() {
            }

            void on_exit() {
            }
    };

    std::shared_ptr<MyState> state1 = std::make_shared<MyState>(0);
    std::shared_ptr<MyState> state2 = std::make_shared<MyState>(1);

    std::map<std::size_t, std::shared_ptr<Nightingale::FSM::FsmState>> map;

    map.emplace(state1->get_id(), state1);
    map.emplace(state2->get_id(), state2);

    Nightingale::FSM::PushdownAutomaton pa(map, state1->get_id());

    ASSERT_EQ(pa.get_current_state_id(), state1->get_id());
    ASSERT_TRUE(pa.get_current_state() == state1);
    
    pa.request_new_state(state2->get_id());
    pa.update();

    ASSERT_EQ(pa.get_current_state_id(), state2->get_id());
    ASSERT_TRUE(pa.get_current_state() == state2);

    pa.return_to_previous_state();
    pa.update();

    ASSERT_EQ(pa.get_current_state_id(), state1->get_id());
    ASSERT_TRUE(pa.get_current_state() == state1);
}
