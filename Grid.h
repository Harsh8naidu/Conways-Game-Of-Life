#pragma once

#include <vector>
#include <string>
#include "GameConfig.h"

class Grid {
public:
    Grid(const GameConfig& config);
    Grid(std::string filename);
    ~Grid();

    void DisplayGrid();

    void PlaceAliveCells();

protected:
    int rows = 0;
    int columns = 0;
    int gridSize = 0;
    int aliveCells = 0;
    int steps = 0;

    std::vector<std::vector<bool>> currentGrid;
};