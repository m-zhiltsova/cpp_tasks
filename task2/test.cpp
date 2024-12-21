#include <gtest/gtest.h>
#include <filesystem>
#include "Universe.h"
// + итерация прошла правильно

TEST(Information, GetName) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    ASSERT_EQ(u.getName(), "TestUniverse");
}

TEST(Information, GetRule) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    ASSERT_EQ(u.getRule(), "B3/S23");
}

TEST(Information, GetCurrentIteration) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    ASSERT_EQ(u.getCurrentIteration(), 0);
}

TEST(Information, GetBirth) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    ASSERT_EQ(u.getBirth(), std::vector<int>({3}));
}

TEST(Information, GetSurvival) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    ASSERT_EQ(u.getSurvival(), std::vector<int>({2, 3}));
}

TEST(Functions, SaveToFile) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.grid[1][1] = true;
    u.grid[2][2] = true;
    Universe universe("Default Universe", "B3/S23", 20, 20);
    //universe.loadFromFile(a);
}

TEST(UniverseTest, LoadFromFile) {
    Universe universe("Default Universe", "B3/S23", 20, 20);
    //universe.loadFromFile(a);
    ASSERT_EQ(universe.getName(), "Test Universe");
    ASSERT_EQ(universe.getRule(), "B3/S23");
    ASSERT_EQ(universe.grid[1][1], true);
    ASSERT_EQ(universe.grid[0][0], true);
    ASSERT_EQ(universe.grid[1][0], false);
}

TEST(Functions, LoadFromFile_EmptyFile) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.loadFromFile("empty_file.txt");
    ASSERT_EQ(u.getName(), "TestUniverse");
    ASSERT_EQ(u.getRule(), "B3/S23");
    ASSERT_EQ(u.grid.size(), 5);
    ASSERT_EQ(u.grid[0].size(), 5);
}

TEST(Functions, LoadFromFile_InvalidFile) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.loadFromFile("invalid_file.rle");
    ASSERT_EQ(u.getName(), "TestUniverse");
    ASSERT_EQ(u.getRule(), "B3/S23");
    ASSERT_EQ(u.grid.size(), 5);
    ASSERT_EQ(u.grid[0].size(), 5);
}

TEST(Functions, SaveToFile_EmptyGrid) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.saveToFile("test_save_empty.rle");
}

TEST(Functions, Tick) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.grid[1][1] = true;
    u.grid[2][2] = true;
    u.tick(1);
    ASSERT_EQ(u.getCurrentIteration(), 1);
}

TEST(Functions, Tick_MultipleIterations) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.grid[1][1] = true;
    u.grid[2][2] = true;
    u.tick(5);
    ASSERT_EQ(u.getCurrentIteration(), 5);
}

TEST(Functions, Tick_EmptyGrid) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.tick(1);
    ASSERT_EQ(u.getCurrentIteration(), 1);
}

TEST(Functions, Print) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.grid[1][1] = true;
    u.grid[2][2] = true;
    testing::internal::CaptureStdout();
    u.print();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("Universe: TestUniverse") != std::string::npos);
    ASSERT_TRUE(output.find("Rule: B3/S23") != std::string::npos);
    ASSERT_TRUE(output.find("Iteration: 0") != std::string::npos);
}

TEST(Functions, Print_EmptyGrid) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    testing::internal::CaptureStdout();
    u.print();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("Universe: TestUniverse") != std::string::npos);
    ASSERT_TRUE(output.find("Rule: B3/S23") != std::string::npos);
    ASSERT_TRUE(output.find("Iteration: 0") != std::string::npos);
}

TEST(Functions, ParseRule) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.parseRule("B3/S23");
}

TEST(Functions, ParseRule_EmptyRule) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.parseRule("");
}

TEST(Functions, ParseRule_InvalidRule) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.parseRule("B/S");
}

TEST(Functions, CountAliveNeighbors) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.grid[1][1] = true;
    u.grid[2][2] = true;
    ASSERT_EQ(u.countAliveNeighbors(1, 1), 1);
    ASSERT_EQ(u.countAliveNeighbors(2, 2), 1);
}

TEST(Functions, CountAliveNeighbors_EdgeCase) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.grid[0][0] = true;
    u.grid[1][1] = true;
    ASSERT_EQ(u.countAliveNeighbors(0, 0), 1);
    ASSERT_EQ(u.countAliveNeighbors(1, 1), 1);
}

TEST(Functions, CountAliveNeighbors_CornerCase) {
    Universe u("TestUniverse", "B3/S23", 5, 5);
    u.grid[0][0] = true;
    u.grid[4][4] = true;
    ASSERT_EQ(u.countAliveNeighbors(0, 0), 1);
    ASSERT_EQ(u.countAliveNeighbors(4, 4), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

