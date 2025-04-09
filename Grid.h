#pragma once

#include <vector>
#include <string>

class Grid {
public:
    Grid(int rows, int columns);
    Grid(std::string filename);
    ~Grid();

    void DisplayGrid();

protected:
    int rows;
    int columns;
    int gridSize;

    std::vector<std::vector<bool>> currentGrid;
};