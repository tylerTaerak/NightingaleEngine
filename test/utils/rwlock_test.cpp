#include <utils/rwlock.hpp>
#include <gtest/gtest.h>

TEST(RwLockTests, ReadTest) {
    class MyClass {
        public:
            MyClass() {
                data = 2;
            }
            int data;
    };

    MyClass *mine = new MyClass;

    Nightingale::Utils::RwLock<MyClass> lock(mine);

    ASSERT_TRUE(lock.read().get_data()->data == mine->data);
}

TEST(RwLockTests, WriteTest) {
    class MyClass {
        public:
            MyClass() {
                data = 2;
            }
            int data;
    };

    MyClass *mine = new MyClass;

    Nightingale::Utils::RwLock<MyClass> lock(mine);

    {
        lock.write().get_data()->data = 3;
    }

    ASSERT_TRUE(lock.read().get_data()->data == 3);
    ASSERT_TRUE(mine->data == lock.read().get_data()->data);
}
