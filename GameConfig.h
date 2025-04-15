#pragma once
#include <string>

struct GameConfig {
    int rows = 0;
    int columns = 0;
    int aliveCells = 0;
    int steps = 0;
    std::string pattern = "";
    int maxAttempts = 0;
};