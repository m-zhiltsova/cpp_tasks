#include <gtest/gtest.h>
#include "/home/wake/Documents/nsu/cpp/cpp_tasks/hw5/src/task.h"

TEST(TimeTest, Creation) {
    Time t1(10, 20, 30);
    EXPECT_EQ(t1.GetHours(), 10);
    EXPECT_EQ(t1.GetMinutes(), 20);
    EXPECT_EQ(t1.GetSeconds(), 30);
}

TEST(TimeTest, AddSeconds) {
    Time t1(10, 20, 30);
    t1 += 50;
    EXPECT_EQ(t1.GetHours(), 10);
    EXPECT_EQ(t1.GetMinutes(), 21);
    EXPECT_EQ(t1.GetSeconds(), 20);
}

TEST(TimeTest, SubtractSeconds) {
    Time t1(10, 20, 30);
    t1 -= 30;
    EXPECT_EQ(t1.GetHours(), 10);
    EXPECT_EQ(t1.GetMinutes(), 20);
    EXPECT_EQ(t1.GetSeconds(), 0);
}

TEST(TimeTest, Normalize) {
    Time t1(10, 90, 70);
    EXPECT_EQ(t1.GetHours(), 11);
    EXPECT_EQ(t1.GetMinutes(), 31);
    EXPECT_EQ(t1.GetSeconds(), 10);
}

TEST(TimeTest, Normalize_with_error) {
    Time t1(10, 90, 70);
    EXPECT_EQ(t1.GetHours(), 10);
    EXPECT_EQ(t1.GetMinutes(), 31);
    EXPECT_EQ(t1.GetSeconds(), 10);
}


TEST(TimeTest, Overflow) {
    Time t1(23, 59, 59);
    t1 += 1;
    EXPECT_EQ(t1.GetHours(), 0);
    EXPECT_EQ(t1.GetMinutes(), 0);
    EXPECT_EQ(t1.GetSeconds(), 0);
}

TEST(TimeTest, NegativeTime) {
    Time t1(0, 0, 0);
    t1 -= 5;
    EXPECT_EQ(t1.GetHours(), 23);
    EXPECT_EQ(t1.GetMinutes(), 59);
    EXPECT_EQ(t1.GetSeconds(), 55);
}

 int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
}   
