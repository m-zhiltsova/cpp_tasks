#include <gtest/gtest.h>
#include "./../src/task1b.h"

TEST(CircularBufferTest, DefaultConstructor) {
    CircularBuffer cb;
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 0);
    EXPECT_TRUE(cb.empty());
}
TEST(CircularBufferTest, ConstructorWithCapacity) {
    CircularBuffer cb(5);
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, ConstructorWithCapacityAndElement) {
    CircularBuffer cb(5, 'a');
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.capacity(), 5);
    for (int i = 0; i < cb.size(); ++i) {
        EXPECT_EQ(cb[i], 'a');
    }
}
TEST(CircularBufferTest, PushBack) {
    CircularBuffer cb(3);
    cb.push_back('x');
    cb.push_back('y');
    cb.push_back('z');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'x');
    EXPECT_EQ(cb[1], 'y');
    EXPECT_EQ(cb[2], 'z');
    cb.push_back('w');
    EXPECT_EQ(cb[0], 'y');
}

TEST(CircularBufferTest, PopBack) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.pop_back();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb[0], 'a');
}

TEST(CircularBufferTest, PushFront) {
    CircularBuffer cb(3);
    cb.push_front('a');
    cb.push_front('b');
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'b');
    EXPECT_EQ(cb[1], 'a');
}

TEST(CircularBufferTest, PopFront) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_front('c');
    cb.pop_front();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'a');
}

TEST(CircularBufferTest, AssignmentOperator) {
    CircularBuffer cb1(3);
    cb1.push_back('x');
    CircularBuffer cb2;
    cb2 = cb1; // Оператор присваивания
    EXPECT_EQ(cb2.size(), 1);
    EXPECT_EQ(cb2[0], 'x');
}

TEST(CircularBufferTest, Linearization) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.linearize();
    EXPECT_TRUE(cb.is_linearized());
}

TEST(CircularBufferTest, Clear) {
    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.clear();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, Insert) {
    CircularBuffer cb(3);
    cb.push_back('x');
    cb.push_back('y');
    cb.insert(1, 'z');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[1], 'z');
}

TEST(CircularBufferTest, Erase) {
    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    cb.erase(0, 2);
    EXPECT_EQ(cb.size(), 1);
}
 
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

