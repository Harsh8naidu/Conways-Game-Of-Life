#include "Grid.h"
#include <iostream>

Grid::Grid(int rows, int columns) : rows(rows), columns(columns), gridSize(rows * columns), currentGrid(rows, std::vector<bool>(columns, false))
{
    DisplayGrid();
}

Grid::Grid(std::string filename)
{
}

void Grid::DisplayGrid()
{
    // Print the top border
    std::cout << ".";
    for (int i = 0; i < columns; i++) {
        std::cout << " .";
    }
    std::cout << std::endl;

    // Print the middle part
    for (int i = 0; i < rows; i++) {
        // For each row print "."
        std::cout << ".";
        // Declare the string inside outer loop to reset it before the next row
        for (int j = 0; j < columns; j++) {
            char cellStatus = currentGrid[i][j] ? 'O' : ' ';
            std::cout << cellStatus << ".";
        }
        std::cout << std::endl;
    }
}
