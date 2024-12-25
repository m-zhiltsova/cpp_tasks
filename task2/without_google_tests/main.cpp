#include "Universe.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    Universe universe("Default Universe", "B3/S23", 20, 20);

    universe.printHelp();

    std::string input_file;
    std::string output_file;
    int iterations = 0;

    universe.parseArguments(argc, argv, input_file, output_file, iterations);

    universe.initializeUniverse(universe, input_file);

    if (iterations > 0) {
        universe.tick(iterations);
        if (!output_file.empty()) {
            universe.saveToFile(output_file);
        }
        return 0;
    }

    universe.processCommands(universe);
    return 0;
}

