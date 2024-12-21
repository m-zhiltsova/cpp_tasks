#include "Universe.h"

Universe::Universe(const std::string& name, const std::string& rule, int width, int height)
    : name(name), rule(rule), width(width), height(height), current_iteration(0) {
    grid.resize(height, std::vector<bool>(width, false));
    parseRule(rule);
}

void Universe::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("#N") == 0) {
            name = line.substr(3);
        } else if (line.find("#R") == 0) {
            rule = line.substr(3);
            parseRule(rule);
        } else if (!line.empty() && line[0] != '!') {
            int x, y;
            if (std::sscanf(line.c_str(), "%d %d", &x, &y) == 2) {
                grid[y][x] = true;
            } else {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
    }
    file.close();
}

void Universe::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "#N " << name << "\n";
    file << "#R " << rule << "\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x]) {
                file << x << " " << y << "\n";
            }
        }
    }
    file.close();
}

void Universe::tick(int n) {
    for (int i = 0; i < n; i++) {
        auto new_grid = grid;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int alive_neighbors = countAliveNeighbors(x, y);
                if (grid[y][x]) {
                    new_grid[y][x] = std::find(survival.begin(), survival.end(), alive_neighbors) != survival.end();
                } else {
                    new_grid[y][x] = std::find(birth.begin(), birth.end(), alive_neighbors) != birth.end();
                }
            }
        }
        grid = new_grid;
        current_iteration++;
    }
}

void Universe::print() const {
    std::cout << "Universe: " << name << "\n";
    std::cout << "Rule: " << rule << "\n";
    std::cout << "Iteration: " << current_iteration << "\n";
    for (const auto& row : grid) {
        for (bool cell : row) {
            std::cout << (cell ? 'O' : '.') << " ";
        }
        std::cout << "\n";
    }
}

void Universe::parseRule(const std::string& rule) {
    if (rule == "") { 
        std::cerr << "Invalid rule" << std::endl;
	return;
    }
    size_t pos = rule.find('/');
    std::string birth_str = rule.substr(1, pos - 1);
    std::string survival_str = rule.substr(pos + 2);

    for (char c : birth_str) {
        if (isdigit(c)) {
            birth.push_back(c - '0');
        }
    }

    for (char c : survival_str) {
        if (isdigit(c)) {
            survival.push_back(c - '0');
        }
    }
}

int Universe::countAliveNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + width) % width;
            int ny = (y + dy + height) % height;
            if (grid[ny][nx]) {
                count++;
            }
        }
    }
    return count;
}
