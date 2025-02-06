#include <ecs/component.hpp>
#include <gtest/gtest.h>

TEST(ComponentTests, CreateComponent) {
    class MyComponent : public Nightingale::ECS::Component {
        public:
            MyComponent()
                : Nightingale::ECS::Component(0) {}
            ~MyComponent(){}
    } c;
    EXPECT_TRUE(&c != nullptr);
}
