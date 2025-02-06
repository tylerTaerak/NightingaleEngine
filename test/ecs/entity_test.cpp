#include "ecs/component.hpp"
#include <ecs/entity.hpp>
#include <gtest/gtest.h>

TEST(EntityTests, CreateEntity) {
    Nightingale::ECS::Entity entity;
    entity = Nightingale::ECS::Entity{}; // create a second entity to make sure that the entity's id is not equal to 0

    ASSERT_TRUE(entity.get_id() > 0);
}

TEST(EntityTests, AddAndCheckComponent) {
    class MyComponent : public Nightingale::ECS::Component {
        public:
            MyComponent()
                : Component(0) {}

            ~MyComponent() {}
    };

    auto myComponent = std::make_shared<MyComponent>();

    Nightingale::ECS::Entity entity;

    entity.add_component(myComponent);

    ASSERT_TRUE(entity.contains_component(0));
    ASSERT_TRUE(entity.contains_component(0));
}

TEST(EntityTests, GetComponent) {
    class MyComponent : public Nightingale::ECS::Component {
        public:
            int id;
            MyComponent()
                : Component(0) {}

            ~MyComponent() {}
    };
    auto myComponent = std::make_shared<MyComponent>();

    myComponent->id = 1;

    Nightingale::ECS::Entity entity;

    entity.add_component(myComponent);

    ASSERT_TRUE(entity.contains_component(0));
    std::shared_ptr<MyComponent> c = std::dynamic_pointer_cast<MyComponent>(entity.get_component(0));
    ASSERT_TRUE(c != nullptr);
    ASSERT_TRUE(c->id == myComponent->id);
}
