#include "ecs/system.hpp"
#include <game_states/game_mode.hpp>
#include <gtest/gtest.h>

TEST(GameModeTests, CreateGameMode) {
    class MyGameMode : public Nightingale::GameStates::GameMode {
        public:
            MyGameMode(std::size_t id)
                : GameMode(id) {
            }
            void on_enter() {
            }

            void on_exit() {
            }
    };

    MyGameMode gm(0);

    ASSERT_TRUE(true);
}

TEST(GameModeTests, AddSystem) {
    class MySystem : public Nightingale::ECS::System {
        public:
            MySystem(std::vector<std::size_t> components) 
                : System(components) {
            }
            void update(const std::vector<std::shared_ptr<Nightingale::Utils::RwLock<Nightingale::ECS::Entity>>> &entities, float frameTime) {
            }
    };

    MySystem sys(std::vector<std::size_t>{});

    class MyGameMode : public Nightingale::GameStates::GameMode {
        public:
            MyGameMode(std::size_t id)
                : GameMode(id) {
                }

            void on_enter() {
            }

            void on_exit() {
            }
    };

    MyGameMode gm(0);

    gm.add_system(sys);

    ASSERT_TRUE(true);
}
