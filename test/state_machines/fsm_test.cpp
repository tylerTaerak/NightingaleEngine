#include <state_machines/fsm.hpp>
#include <gtest/gtest.h>
#include <utils/logger.hpp>

TEST(FSMTests, CreateFSMState) {
    class MyState : public Nightingale::FSM::FsmState {
        public:
            MyState(std::size_t id) 
                : FsmState(id) {
            }

            void on_enter() {
            }

            void on_exit() {
            }
    };

    MyState state(0);

    ASSERT_TRUE(true);
}

TEST(FSMTests, CreateFSM) {
    class MyState : public Nightingale::FSM::FsmState {
        public:
            MyState(std::size_t id)
                : FsmState(id) {
            }

            void on_enter() {
            }

            void on_exit() {
            }
    };

    auto state = std::make_shared<MyState>(0);

    std::map<std::size_t, std::shared_ptr<Nightingale::FSM::FsmState>> map;

    map.emplace(state->get_id(), state);

    Nightingale::FSM::FSM fsm(map, state->get_id());

    ASSERT_TRUE(fsm.get_current_state() != nullptr);
    ASSERT_TRUE(fsm.get_current_state() == state);
}

TEST(FSMTests, SwitchStates) {
    class MyState : public Nightingale::FSM::FsmState {
        public:
            MyState(std::size_t id)
                : FsmState(id) {
            }

            void on_enter() {
            }

            void on_exit() {
            }
    };

    auto state1 = std::make_shared<MyState>(0);
    auto state2 = std::make_shared<MyState>(1);

    std::map<std::size_t, std::shared_ptr<Nightingale::FSM::FsmState>> map;

    map.emplace(state1->get_id(), state1);
    map.emplace(state2->get_id(), state2);

    Nightingale::FSM::FSM fsm(map, state1->get_id());

    fsm.request_new_state(state2->get_id());

    fsm.update();

    ASSERT_TRUE(fsm.get_current_state_id() == state2->get_id());
    ASSERT_TRUE(fsm.get_current_state() == state2);
}

TEST(FSMTests, OnEnterTest) {
    class MyState : public Nightingale::FSM::FsmState {
        public:
            MyState(std::size_t id)
                : FsmState(id) {
                    state_id = 0;
            }

            void on_enter() {
                state_id = 10;
            }

            void on_exit() {
            }

            int state_id;
    };

    auto state1 = std::make_shared<MyState>(0);
    auto state2 = std::make_shared<MyState>(1);

    std::map<std::size_t, std::shared_ptr<Nightingale::FSM::FsmState>> map;

    map.emplace(state1->get_id(), state1);
    map.emplace(state2->get_id(), state2);

    Nightingale::FSM::FSM fsm(map, state1->get_id());

    fsm.request_new_state(state2->get_id());

    fsm.update();

    ASSERT_TRUE(state1->state_id == 10);
    ASSERT_TRUE(state2->state_id == 10);
}

TEST(FSMTests, OnExitTest) {
    class MyState : public Nightingale::FSM::FsmState {
        public:
            MyState(std::size_t id)
                : FsmState(id) {
                    state_id = 0;
            }

            void on_enter() {
            }

            void on_exit() {
                state_id = 10;
            }

            int state_id;
    };

    auto state1 = std::make_shared<MyState>(0);
    auto state2 = std::make_shared<MyState>(1);

    std::map<std::size_t, std::shared_ptr<Nightingale::FSM::FsmState>> map;

    map.emplace(state1->get_id(), state1);
    map.emplace(state2->get_id(), state2);

    Nightingale::FSM::FSM fsm(map, state1->get_id());

    fsm.request_new_state(state2->get_id());

    fsm.update();

    ASSERT_EQ(state1->state_id, 10);
    ASSERT_EQ(state2->state_id, 0);
}
