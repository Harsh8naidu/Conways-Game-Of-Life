#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>

#include "Grid.h"
#include "ConsoleUtils.h"

Grid::Grid(const GameConfig& config, PauseController* pauseController) 
    : rows(config.rows), columns(config.columns), gridSize(config.rows * config.columns), aliveCells(config.aliveCells), 
      steps(config.steps), currentGrid(config.rows, std::vector<bool>(config.columns, false)), pauseController(pauseController) {
    PlaceAliveCells(); // randomly set alive cells
}

void Grid::DisplayGrid() {
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

void Grid::DisplayGrid(const std::vector<std::vector<bool>>& gridToDisplay) {
    int rows = gridToDisplay.size();
    if (rows == 0) return;

    int columns = gridToDisplay[0].size();

    std::cout << ".";
    for (int i = 0; i < columns; i++) {
        std::cout << " .";
    }
    std::cout << std::endl;

    for (int i = 0; i < rows; i++) {
        std::cout << ".";
        for (int j = 0; j < columns; j++) {
            char cellStatus = gridToDisplay[i][j] ? 'O' : ' ';
            std::cout << cellStatus << ".";
        }
        std::cout << std::endl;
    }
}


void Grid::PlaceAliveCells() {
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

int Grid::CountLiveNeighbours(int row, int column) {
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

void Grid::SimulateStep() {
    std::vector<std::vector<bool>> nextGrid = std::vector<std::vector<bool>>(rows, std::vector<bool>(columns, false));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int liveNeighbours = CountLiveNeighbours(i, j);
            // if the current cell is alive
            if (currentGrid[i][j]) {
                if (currentGrid[i][j] && liveNeighbours < 2) { // if an alive cell has fewer than two live neighbours -> dies (underpopulation)
                    nextGrid[i][j] = false;
                } else if (currentGrid[i][j] && (liveNeighbours == 2 || liveNeighbours == 3)) { // if an alive cell has two or three live neighbours -> lives
                    nextGrid[i][j] = true;
                } else if (currentGrid[i][j] && liveNeighbours > 3) { // if an live cell has more than three live neighbours -> dies (overpopulation)
                    nextGrid[i][j] = false;
                }
            } else if (!currentGrid[i][j] && liveNeighbours == 3) { // if a dead cell has exactly three live neighbours -> becomes live cell (reproduction)
                nextGrid[i][j] = true;
            }
        }
    }
    currentGrid = nextGrid;
}

void Grid::RunSimulation(int delayMs) {
    isRunning = true;
    int runSteps = steps == 0 ? INT_MAX : steps;  // default to 1 step if steps not set

    for (int i = 0; i < runSteps && isRunning; i++) {
        {
            std::unique_lock<std::mutex> lock(pauseController->mtx);
            pauseController->cv.wait(lock, [this]() { return !pauseController->isPaused; });
        }

        SimulateAndDisplayStep(delayMs);
    }
}

void Grid::SimulateAndDisplayStep(int delayMs) {
    static auto previousTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - previousTime;

    if (elapsed.count() < delayMs / 1000.0f) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs) - elapsed);
    }

    previousTime = std::chrono::high_resolution_clock::now();
    ClearConsole();
    SimulateStep();
    DisplayGrid();
    std::cout << std::endl;
}
