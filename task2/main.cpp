#include "Universe.h"

void printHelp() {
    std::cout << "Commands:\n";
    std::cout << "  dump <filename> - save the universe to a file\n";
    std::cout << "  tick <n=1> (or t <n=1>) - calculate n iterations and print the result\n";
    std::cout << "  exit - quit the game\n";
    std::cout << "  help - print this help message\n";
}

int main(int argc, char* argv[]) {
    std::string input_file;
    std::string output_file;
    int iterations = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-i" || arg == "--iterations") {
            if (i + 1 < argc) {
                iterations = std::atoi(argv[++i]);
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                output_file = argv[++i];
            }
        } else {
            input_file = arg;
        }
    }

    Universe universe("Default Universe", "B3/S23", 20, 20);
    if (!input_file.empty()) {
        universe.loadFromFile(input_file);
    } else {
        std::srand(std::time(0));
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                universe.grid[y][x] = std::rand() % 2 == 0;
            }
        }
    }

    if (iterations > 0) {
        universe.tick(iterations);
        if (!output_file.empty()) {
            universe.saveToFile(output_file);
        }
        return 0;
    }

    std::string command;
    while (true) {
        std::cout << "> ";
        std::cin >> command;
        if (command == "dump") {
            std::string filename;
            std::cin >> filename;
            universe.saveToFile(filename);
        } else if (command == "tick" || command == "t") {
            int n;
            if (std::cin.peek() != '\n') {
                std::cin >> n;
            }
            universe.tick(n);
            universe.print();
        } else if (command == "exit") {
            break;
        } else if (command == "help") {
            printHelp();
        } else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}

