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
    int rows = 0;
    int columns = 0;
    int gridSize = 0;

    std::vector<std::vector<bool>> currentGrid;
};