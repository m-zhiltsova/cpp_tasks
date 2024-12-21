#include <gtest/gtest.h>
#include "./../src/task1b.h"



// Testing constructors
TEST(ConstructorTests, DefaultConstructor) {
    CircularBuffer cb;
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 0);
    EXPECT_TRUE(cb.empty());
    EXPECT_TRUE(cb.full());
}

TEST(ConstructorTests, CapacityConstructor) {
    CircularBuffer cb(5);
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
}

TEST(ConstructorTests, FillConstructor) {
    CircularBuffer cb(3, 'x');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.capacity(), 3);
    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb.full());
    EXPECT_EQ(cb[0], 'x');
    EXPECT_EQ(cb[1], 'x');
    EXPECT_EQ(cb[2], 'x');
}

TEST(ConstructorTests, CopyConstructor) {
    CircularBuffer cb1(3, 'a');
    CircularBuffer cb2(cb1);
    EXPECT_EQ(cb2.size(), cb1.size());
    EXPECT_EQ(cb2.capacity(), cb1.capacity());
    EXPECT_TRUE(cb2.full());
    for (int i = 0; i < cb2.size(); ++i) {
        EXPECT_EQ(cb2[i], 'a');
    }
}

// Testing push and pop methods
TEST(PushPopTests, PushBack) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_TRUE(cb.full());
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'b');
    EXPECT_EQ(cb[2], 'c');

    // Overflow buffer
    cb.push_back('d');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'b');
    EXPECT_EQ(cb[1], 'c');
    EXPECT_EQ(cb[2], 'd');
}

TEST(PushPopTests, PushFront) {
    CircularBuffer cb(3);
    cb.push_front('a');
    cb.push_front('b');
    cb.push_front('c');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_TRUE(cb.full());
    EXPECT_EQ(cb[0], 'c');
    EXPECT_EQ(cb[1], 'b');
    EXPECT_EQ(cb[2], 'a');

    // Overflow buffer
    cb.push_front('d');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'd');
    EXPECT_EQ(cb[1], 'c');
    EXPECT_EQ(cb[2], 'b');
}

TEST(PushPopTests, PopMethods) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb.pop_back();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'b');

    cb.pop_front();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb[0], 'b');

    cb.pop_back();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());

    // Attempt to delete from empty buffer
    EXPECT_THROW(cb.pop_front(), std::out_of_range);
    EXPECT_THROW(cb.pop_back(), std::out_of_range);
}

// Testing access methods
TEST(AccessTests, AccessMethods) {
    CircularBuffer cb(3);
    cb.push_back('x');
    cb.push_back('y');
    cb.push_back('z');

    EXPECT_EQ(cb.at(0), 'x');
    EXPECT_EQ(cb.at(1), 'y');
    EXPECT_EQ(cb.at(2), 'z');

    cb[1] = 'a';
    EXPECT_EQ(cb[1], 'a');

    // Check out of bounds
    EXPECT_THROW(cb.at(-1), std::out_of_range);
    EXPECT_THROW(cb.at(3), std::out_of_range);
}

TEST(AccessTests, FrontBackMethods) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');

    EXPECT_EQ(cb.front(), 'a');
    EXPECT_EQ(cb.back(), 'b');

    cb.push_back('c');
    EXPECT_EQ(cb.back(), 'c');

    cb.clear();
    EXPECT_THROW(cb.front(), std::out_of_range);
    EXPECT_THROW(cb.back(), std::out_of_range);
}

TEST(LinearizeTests, Linearize) {
    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    cb.push_back('d');
    cb.pop_front();
    cb.push_back('e');

    EXPECT_FALSE(cb.is_linearized());

    value_type* data = cb.linearize();
    EXPECT_TRUE(cb.is_linearized());
    EXPECT_EQ(data[0], 'b');
    EXPECT_EQ(data[1], 'c');
    EXPECT_EQ(data[2], 'd');
    EXPECT_EQ(data[3], 'e');
}

TEST(RotateTests, Rotate) {
    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    cb.push_back('d');
    cb.push_back('e');

    cb.rotate(2); 
    EXPECT_EQ(cb[0], 'c');
    EXPECT_EQ(cb[1], 'd');
    EXPECT_EQ(cb[2], 'e');
    EXPECT_EQ(cb[3], 'a');
    EXPECT_EQ(cb[4], 'b');

    cb.rotate(3); 
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'b');
    EXPECT_EQ(cb[2], 'c');
    EXPECT_EQ(cb[3], 'd');
    EXPECT_EQ(cb[4], 'e');
    EXPECT_THROW(cb.rotate(5), std::out_of_range);
}


TEST(ReserveTests, Reserve) {
    CircularBuffer cb(5);

    EXPECT_EQ(cb.reserve(), 5);

    cb.push_back('a');
    EXPECT_EQ(cb.reserve(), 4);

    cb.push_back('b');
    EXPECT_EQ(cb.reserve(), 3);

    cb.push_back('c');
    EXPECT_EQ(cb.reserve(), 2);

    cb.push_back('d');
    EXPECT_EQ(cb.reserve(), 1);

    cb.push_back('e');
    EXPECT_EQ(cb.reserve(), 0);

    cb.pop_front();
    EXPECT_EQ(cb.reserve(), 1);

    cb.pop_front();
    EXPECT_EQ(cb.reserve(), 2);

}

TEST(ReserveTests, ReserveWithCapacityChange) {
    CircularBuffer cb(3);

    EXPECT_EQ(cb.reserve(), 3);
    cb.push_back('a');
    EXPECT_EQ(cb.reserve(), 2);

    cb.push_back('b');
    EXPECT_EQ(cb.reserve(), 1);

    cb.push_back('c');
    EXPECT_EQ(cb.reserve(), 0);

    cb.set_capacity(5);
    EXPECT_EQ(cb.reserve(), 2);

    cb.push_back('d');
    EXPECT_EQ(cb.reserve(), 1);

    cb.push_back('e');
    EXPECT_EQ(cb.reserve(), 0);

    cb.set_capacity(4);
    EXPECT_EQ(cb.reserve(), 0);

    cb.pop_front();
    EXPECT_EQ(cb.reserve(), 1);

    cb.pop_front();
    EXPECT_EQ(cb.reserve(), 2);

}

TEST(SwapTests, Swap) {
    CircularBuffer cb1(3, 'a');
    CircularBuffer cb2(2, 'b');

    cb1.swap(cb2);

    EXPECT_EQ(cb1.capacity(), 2);
    EXPECT_EQ(cb1.size(), 2);
    EXPECT_EQ(cb1[0], 'b');
    EXPECT_EQ(cb1[1], 'b');

    EXPECT_EQ(cb2.capacity(), 3);
    EXPECT_EQ(cb2.size(), 3);
    EXPECT_EQ(cb2[0], 'a');
    EXPECT_EQ(cb2[1], 'a');
    EXPECT_EQ(cb2[2], 'a');

    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb.swap(cb);

    ASSERT_EQ(cb.size(), 3);
    ASSERT_EQ(cb[0], 'a');
    ASSERT_EQ(cb[1], 'b');
    ASSERT_EQ(cb[2], 'c');

}

TEST(ResizeTests, Resize) {
    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb.resize(5, 'x');
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'b');
    EXPECT_EQ(cb[2], 'c');
    EXPECT_EQ(cb[3], 'x');
    EXPECT_EQ(cb[4], 'x');

    cb.resize(2);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'b');

    EXPECT_THROW(cb.resize(6), std::invalid_argument);
}

TEST(CapacityTests, SetCapacity) {
    CircularBuffer cb(3, 'a');
    cb.set_capacity(5);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 3);
    cb.push_back('b');
    cb.push_back('c');
    EXPECT_EQ(cb.size(), 5);

    cb.set_capacity(2);
    EXPECT_EQ(cb.capacity(), 2);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'a');
}
TEST(InsertTests, Insert) {
    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb.insert(1, 'x');
    EXPECT_EQ(cb.size(), 4);
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'x');
    EXPECT_EQ(cb[2], 'b');
    EXPECT_EQ(cb[3], 'c');

    cb.insert(4, 'y');
    EXPECT_EQ(cb.size(), 5);
    EXPECT_THROW(cb.insert(5, 'z'), std::out_of_range);

    EXPECT_THROW(cb.insert(-1, 'w'), std::out_of_range);
    EXPECT_THROW(cb.insert(6, 'w'), std::out_of_range);
}

TEST(EraseTests, Erase) {
    CircularBuffer cb(5, 'a');

    cb.erase(1, 3);
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb[1], 'a');
    EXPECT_EQ(cb[2], 'a');

    EXPECT_THROW(cb.erase(2, 1), std::out_of_range);
    EXPECT_THROW(cb.erase(-1, 2), std::out_of_range);
    EXPECT_THROW(cb.erase(0, 4), std::out_of_range);
}

TEST(ClearTests, Clear) {
    CircularBuffer cb(3, 'a');
    cb.clear();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
}

TEST(AssignmentTests, AssignmentOperator) {
    CircularBuffer cb1(3, 'a');
    CircularBuffer cb2(2, 'b');
    cb2 = cb1;

    EXPECT_EQ(cb2.capacity(), 3);
    EXPECT_EQ(cb2.size(), 3);
    EXPECT_EQ(cb2[0], 'a');
    EXPECT_EQ(cb2[1], 'a');
    EXPECT_EQ(cb2[2], 'a');

    CircularBuffer cb(5);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb = cb;

    ASSERT_EQ(cb.size(), 3);
    ASSERT_EQ(cb[0], 'a');
    ASSERT_EQ(cb[1], 'b');
    ASSERT_EQ(cb[2], 'c');
}

TEST(EqualityTests, EqualityOperators) {
    CircularBuffer cb1(3, 'a');
    CircularBuffer cb2(3, 'a');
    CircularBuffer cb3(3, 'b');

    EXPECT_TRUE(cb1 == cb2);
    EXPECT_TRUE(cb1 != cb3);

    cb2.push_back('b');
    EXPECT_TRUE(cb1 != cb2);
}

TEST(ExceptionTests, ConstructorExceptions) {
    EXPECT_THROW(CircularBuffer cb(-1), std::invalid_argument);
    EXPECT_THROW(CircularBuffer cb(-5, 'x'), std::invalid_argument);
}

TEST(ExceptionTests, MethodExceptions) {
    CircularBuffer cb(3);

    // Access by invalid index
    EXPECT_THROW(cb.at(0), std::out_of_range);
    cb.push_back('a');
    EXPECT_NO_THROW(cb.at(0));
    EXPECT_THROW(cb.at(1), std::out_of_range);

    // Set capacity to invalid value
    EXPECT_THROW(cb.set_capacity(-1), std::invalid_argument);

    // Resize to invalid size
    EXPECT_THROW(cb.resize(-1), std::invalid_argument);
    EXPECT_THROW(cb.resize(5), std::invalid_argument);

    // Rotate to invalid index
    EXPECT_THROW(cb.rotate(-1), std::out_of_range);
    EXPECT_THROW(cb.rotate(2), std::out_of_range);
}

TEST(OverwriteTests, OverwriteBehavior) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb.push_back('d');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'b');
    EXPECT_EQ(cb[1], 'c');
    EXPECT_EQ(cb[2], 'd');

    cb.push_front('e');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'e');
    EXPECT_EQ(cb[1], 'b');
    EXPECT_EQ(cb[2], 'c');
}

TEST(EdgeCases, EmptyBuffer) {
    CircularBuffer cb(3);
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 3);
}

TEST(EdgeCases, FullBuffer) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb.full());
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.capacity(), 3);
}

TEST(EdgeCases, SingleElement) {
    CircularBuffer cb(1);
    cb.push_back('a');
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 1);
    EXPECT_EQ(cb.front(), 'a');
    EXPECT_EQ(cb.back(), 'a');
}

TEST(Capasity, PushBackEmptyBuffer) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_back('a');
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 'a');
    EXPECT_EQ(cb.back(), 'a');
}

TEST(Capasity, PushBackFullBuffer) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    EXPECT_TRUE(cb.full());
    cb.push_back('d');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.front(), 'b');
    EXPECT_EQ(cb.back(), 'd');
}

TEST(Capasity, PushFrontEmptyBuffer) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_front('a');
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 'a');
    EXPECT_EQ(cb.back(), 'a');
}

TEST(Capasity, PushFrontFullBuffer) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_front('a');
    cb.push_front('b');
    cb.push_front('c');
    EXPECT_TRUE(cb.full());
    cb.push_front('d');
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.front(), 'd');
    EXPECT_EQ(cb.back(), 'b');
}

TEST(Capasity, PopBackEmptyBuffer) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    EXPECT_THROW(cb.pop_back(), std::out_of_range);
}

TEST(Capasity, PopBackSingleElement) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_back('a');
    cb.pop_back();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
}

TEST(Capasity, PopBackMultipleElements) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    cb.pop_back();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.back(), 'b');
    cb.pop_back();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 'a');
    cb.pop_back();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
}

TEST(Capasity, PopFrontEmptyBuffer) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    EXPECT_THROW(cb.pop_front(), std::out_of_range);
}

TEST(Capasity, PopFrontSingleElement) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_front('a');
    cb.pop_front();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
}

TEST(Capasity, PopFrontMultipleElements) {
    CircularBuffer cb(3);
    EXPECT_EQ(cb.capacity(), 3);
    cb.push_front('a');
    cb.push_front('b');
    cb.push_front('c');
    cb.pop_front();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 'b');
    cb.pop_front();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 'a');
    cb.pop_front();
    EXPECT_EQ(cb.size(), 0);
    EXPECT_TRUE(cb.empty());
}
TEST(Looping, PushBack) {
    CircularBuffer cb(3);

    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    ASSERT_TRUE(cb.full());
    ASSERT_EQ(cb.front(), 'a');
    ASSERT_EQ(cb.back(), 'c');

    cb.push_back('d');
    ASSERT_EQ(cb.front(), 'b');
    ASSERT_EQ(cb.back(), 'd');
    ASSERT_EQ(cb.size(), 3);

    cb.push_back('e');
    ASSERT_EQ(cb.front(), 'c');
    ASSERT_EQ(cb.back(), 'e');
    ASSERT_EQ(cb.size(), 3);

    cb.push_back('f');
    ASSERT_EQ(cb.front(), 'd');
    ASSERT_EQ(cb.back(), 'f');
    ASSERT_EQ(cb.size(), 3);
}

TEST(Looping, PopBack) {
    CircularBuffer cb(3);

    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb.pop_back();
    ASSERT_EQ(cb.back(), 'b');
    ASSERT_EQ(cb.size(), 2);

    cb.pop_back();
    ASSERT_EQ(cb.back(), 'a');
    ASSERT_EQ(cb.size(), 1);

    cb.pop_back();
    ASSERT_TRUE(cb.empty());
}

TEST(Looping, PushFront) {
    CircularBuffer cb(3);

    cb.push_front('a');
    cb.push_front('b');
    cb.push_front('c');
    ASSERT_TRUE(cb.full());
    ASSERT_EQ(cb.front(), 'c');
    ASSERT_EQ(cb.back(), 'a');

    cb.push_front('d');
    ASSERT_EQ(cb.front(), 'd');
    ASSERT_EQ(cb.back(), 'b');
    ASSERT_EQ(cb.size(), 3);

    cb.push_front('e');
    ASSERT_EQ(cb.front(), 'e');
    ASSERT_EQ(cb.back(), 'c');
    ASSERT_EQ(cb.size(), 3);

    cb.push_front('f');
    ASSERT_EQ(cb.front(), 'f');
    ASSERT_EQ(cb.back(), 'd');
    ASSERT_EQ(cb.size(), 3);
}

TEST(Looping, PopFront) {
    CircularBuffer cb(3);

    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');

    cb.pop_front();
    ASSERT_EQ(cb.front(), 'b');
    ASSERT_EQ(cb.size(), 2);

    cb.pop_front();
    ASSERT_EQ(cb.front(), 'c');
    ASSERT_EQ(cb.size(), 1);

    cb.pop_front();
    ASSERT_TRUE(cb.empty());
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

