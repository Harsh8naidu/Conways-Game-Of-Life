#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>

#include "Grid.h"
#include "ConsoleUtils.h"

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

int Grid::CountLiveNeighbours(int row, int column)
{
    // Define the 8 offsets for neighbours (row_offset, col_offset)
    int offset[8][2] = {
        {-1, -1}, {-1, 0}, {-1, +1}, // Top-left, Top-middle, Top-right
        {0, -1}, {0, +1},           // Middle-left, Middle-right
        {+1, -1}, {+1, 0}, {+1, +1}  // Bottom-left, Bottom-middle, Bottom-right
    };

    int liveNeighbours = 0;
    // Iterate through each neighbour using offsets
    for (int k = 0; k < 8; k++) {
        int neighbourRow = row + offset[k][0]; // Calculate neighbour row's
        int neighbourColumn = column + offset[k][1]; // Calculate neighbour column's

        // Check if neighbour is within bounds
        if (neighbourRow >= 0 && neighbourRow < rows && neighbourColumn >= 0 && neighbourColumn < columns) {
            if (currentGrid[neighbourRow][neighbourColumn]) {
                liveNeighbours++; // Count live neighbours
            }
        }
    }
    return liveNeighbours;
}

void Grid::SimulateStep()
{
    std::vector<std::vector<bool>> nextGrid = std::vector<std::vector<bool>>(rows, std::vector<bool>(columns, false));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int liveNeighbours = CountLiveNeighbours(i, j);
            // if the current cell is alive
            if (currentGrid[i][j]) {
                // if an alive cell has fewer than two live neighbours -> dies (underpopulation)
                if (currentGrid[i][j] && liveNeighbours < 2) {
                    nextGrid[i][j] = false;
                }
                // if an alive cell has two or three live neighbours -> lives
                else if (currentGrid[i][j] && (liveNeighbours == 2 || liveNeighbours == 3)) {
                    nextGrid[i][j] = true;
                }
                // if an live cell has more than three live neighbours -> dies (overpopulation)
                else if (currentGrid[i][j] && liveNeighbours > 3) {
                    nextGrid[i][j] = false;
                }
            }
            // if a dead cell has exactly three live neighbours -> becomes live cell (reproduction)
            else if (!currentGrid[i][j] && liveNeighbours == 3) {
                nextGrid[i][j] = true;
            }
            
        }
    }

    currentGrid = nextGrid;
}

void Grid::RunSimulation(int delayMs)
{
    for (int i = 0; i < steps; i++) {
        ClearConsole(); // Clear the console before printing the next grid
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        SimulateStep();
        DisplayGrid();
        std::cout << std::endl;
    }
}