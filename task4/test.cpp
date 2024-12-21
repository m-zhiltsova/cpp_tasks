#include <gtest/gtest.h>
#include <sstream>
#include <tuple>
#include <vector>
#include <stdexcept>
#include "CSVParser.h"

TEST(CSVParserTest, BasicParsing) {
    std::istringstream input("1,hello\n2,world\n");
    CSVParser<int, std::string> parser(input);

    auto it = parser.begin();
    ASSERT_EQ(std::make_tuple(1, "hello"), *it);
    ++it;
    ASSERT_EQ(std::make_tuple(2, "world"), *it);
    ++it;
    ASSERT_EQ(parser.end(), it);
}

TEST(CSVParserTest, SkipLines) {
    std::istringstream input("header1,header2\n1,hello\n2,world\n");
    CSVParser<int, std::string> parser(input, 1);

    auto it = parser.begin();
    ASSERT_EQ(std::make_tuple(1, "hello"), *it);
    ++it;
    ASSERT_EQ(std::make_tuple(2, "world"), *it);
    ++it;
    ASSERT_EQ(parser.end(), it);
}

TEST(CSVParserTest, IncorrectColumnCount) {
    std::istringstream input("1,hello\n2\n");
    CSVParser<int, std::string> parser(input);

    auto it = parser.begin();
    ASSERT_EQ(std::make_tuple(1, "hello"), *it);
    ASSERT_THROW(++it, std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

