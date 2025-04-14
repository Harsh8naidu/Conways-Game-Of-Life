#pragma once
#include <string>

struct GameConfig {
    int rows;
    int columns;
    int aliveCells;
    int steps;
    std::string pattern;
    int maxAttempts;
};