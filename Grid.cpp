#include "Grid.h"
#include <iostream>

Grid::Grid(int rows, int columns) : rows(rows), columns(columns), currentGrid(rows, std::vector<bool>(columns, false))
{
    DisplayGrid();
}

Grid::Grid(std::string filename)
{
}

void Grid::DisplayGrid()
{
    for (int i = 0; i < rows; i++) {
        // Declare the string inside outer loop to reset it before the next row
        std::string s = "";
        for (int j = 0; j < columns; j++) {
            if (i != rows) { // Check if row ends here
                if (!currentGrid[i][j]) {
                    s += " ";
                }
                else if (currentGrid[i][j]) {
                    s += "O";
                }
            }
        }
        std::cout << s << std::endl;
    }
}
