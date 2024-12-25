#include <iostream>
#include <fstream>
#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");

    // Нужно написать соответсвующий шаблон
    CSVParser<std::string, int, int> parser(file, 0);
    for (auto rs : parser) {
        std::cout << rs << std::endl;
    }
    return 0;
}
