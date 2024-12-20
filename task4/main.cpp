#include <iostream>
#include <fstream>
#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    CSVParser<int, std::string> parser(file, 0);
    for (auto rs : parser) {
        std::cout << rs << std::endl;
    }
    return 0;
}

