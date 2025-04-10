#include <iostream>
#include <fstream>
#include <random>

#include "Grid.h"

Grid::Grid(const GameConfig& config) 
    : rows(config.rows), columns(config.columns), gridSize(config.rows * config.columns), aliveCells(config.aliveCells), 
      steps(config.steps), currentGrid(config.rows, std::vector<bool>(config.columns, false))
{
    PlaceAliveCells(); // randomly set alive cells
}

Grid::Grid(std::string filename)
{
    std::ifstream filestream(filename);

    if (!filestream.is_open()) {
        std::cerr << "File not found!" << std::endl;
        return;
    }

    // Read the filestream and assign the values
    filestream >> rows;
    filestream >> columns;
    filestream.close();

    gridSize = rows * columns;
    currentGrid = std::vector<std::vector<bool>>(rows, std::vector<bool>(columns, true));

    DisplayGrid();
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

void Grid::PlaceAliveCells()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> rowDist(0, rows - 1);
    std::uniform_int_distribution<> columnDist(0, columns - 1);

    int placed = 0;
    while (placed < aliveCells) {
        int r = rowDist(rng);
        int c = columnDist(rng);

        // Set the cell to true only if it is dead (false)
        if (!currentGrid[r][c]) {
            currentGrid[r][c] = true;
            placed++;
        }
    }
}
