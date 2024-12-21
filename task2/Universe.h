#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Universe {
public:
    Universe(const std::string& name, const std::string& rule, int width, int height);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void tick(int n);
    void print() const;

    std::vector<std::vector<bool>> grid;

    std::string getName() const { return name; }
    std::string getRule() const { return rule; }
    int getCurrentIteration() const { return current_iteration; }
    int countAliveNeighbors(int x, int y) const;
    const std::vector<int>   getBirth() const {return birth; }
    const std::vector<int>   getSurvival() const {return survival; }
    void parseRule(const std::string& rule);
private:
    std::string name;
    std::string rule;
    int width;
    int height;
    int current_iteration;
    std::vector<int> birth;
    std::vector<int> survival;
};

#endif // UNIVERSE_H
