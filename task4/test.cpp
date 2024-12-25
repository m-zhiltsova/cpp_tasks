#include <gtest/gtest.h>
#include <sstream>
#include "CSVParser.h"

// Тесты для конструктора CSVParser
TEST(ConstructorTests, Constructor) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    EXPECT_FALSE(parser.begin() == parser.end());
}

TEST(ConstructorTests, ConstructorWithSkipLines) {
    std::istringstream input("Header1,Header2\n1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input, 1);
    EXPECT_FALSE(parser.begin() == parser.end());
}

// Тесты для метода begin
TEST(BeginTests, Begin) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    EXPECT_EQ(std::get<0>(*it), 1);
    EXPECT_EQ(std::get<1>(*it), "John");
}

TEST(BegitTests, BeginWithSkipLines) {
    std::istringstream input("Header1,Header2\n1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input, 1);
    auto it = parser.begin();
    EXPECT_EQ(std::get<0>(*it), 1);
    EXPECT_EQ(std::get<1>(*it), "John");
}

// Тесты для метода end
TEST(EndTests, End) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.end();
    EXPECT_TRUE(it == parser.end());
}

// Тесты для оператора ++
TEST(OperatorsTests, IncrementOperator) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    ++it;
    EXPECT_EQ(std::get<0>(*it), 2);
    EXPECT_EQ(std::get<1>(*it), "Jane");
}

TEST(OperatorsTests, IncrementOperatorToEnd) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    ++it;
    ++it;
    ++it;
    EXPECT_TRUE(it == parser.end());
}

// Тесты для оператора !=
TEST(OperatorsTests, NotEqualOperator) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    EXPECT_TRUE(it != parser.end());
}

TEST(OperatorsTests, NotEqualOperatorAtEnd) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    ++it;
    ++it;
    ++it;
    EXPECT_FALSE(it != parser.end());
}

// Тесты для оператора ==
TEST(OperatorsTests, EqualOperator) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    ++it;
    ++it;
    ++it;
    EXPECT_TRUE(it == parser.end());
}

TEST(OperatorsTests, EqualOperatorNotAtEnd) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    EXPECT_FALSE(it == parser.end());
}

// Тесты для оператора *
TEST(OperatorsTests, DereferenceOperator) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    EXPECT_EQ(std::get<0>(*it), 1);
    EXPECT_EQ(std::get<1>(*it), "John");
}


// Тесты для обработки некорректного количества столбцов

TEST(IncorrectColumnCount, IncorrectColumnCountAtFirstLine) {
    std::istringstream input("1,John,Extra\n2,Jane\n3,Doe\n");
    CSVParser<int, std::string> parser(input);
    EXPECT_THROW(parser.begin(), std::runtime_error);
}


// Тесты для обработки пустых строк
TEST(EmptyLinesTests, EmptyLines) {
    std::istringstream input("\n\n1,John\n\n2,Jane\n\n3,Doe\n\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    EXPECT_EQ(std::get<0>(*it), 1);
    EXPECT_EQ(std::get<1>(*it), "John");
    ++it;
    EXPECT_EQ(std::get<0>(*it), 2);
    EXPECT_EQ(std::get<1>(*it), "Jane");
    ++it;
    EXPECT_EQ(std::get<0>(*it), 3);
    EXPECT_EQ(std::get<1>(*it), "Doe");
    ++it;
    EXPECT_TRUE(it == parser.end());
}

TEST(CEmptyLinesTests, EmptyLinesAtEnd) {
    std::istringstream input("1,John\n2,Jane\n3,Doe\n\n\n");
    CSVParser<int, std::string> parser(input);
    auto it = parser.begin();
    EXPECT_EQ(std::get<0>(*it), 1);
    EXPECT_EQ(std::get<1>(*it), "John");
    ++it;
    EXPECT_EQ(std::get<0>(*it), 2);
    EXPECT_EQ(std::get<1>(*it), "Jane");
    ++it;
    EXPECT_EQ(std::get<0>(*it), 3);
    EXPECT_EQ(std::get<1>(*it), "Doe");
    ++it;
    EXPECT_TRUE(it == parser.end());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

