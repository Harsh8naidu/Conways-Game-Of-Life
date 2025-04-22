#pragma once

#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

#include "GameConfig.h"

class Grid {
public:
    Grid(const GameConfig& config);
    Grid(std::string filename);

    const std::vector<std::vector<bool>>& GetCurrentGrid() const { return currentGrid; };

    void DisplayGrid();
    static void DisplayGrid(const std::vector<std::vector<bool>>& gridToDisplay);
    void PlaceAliveCells();
    int CountLiveNeighbours(int row, int column);
    void SimulateStep();
    void RunSimulation(int delayMs = 300); // Calls SimulateStep() 'steps' times

    void SimulateAndDisplayStep(int delayMs);

    std::atomic<bool> isRunning{ false };
    std::thread simulationThread;

protected:
    int rows = 0;
    int columns = 0;
    int gridSize = 0;
    int aliveCells = 0;
    int steps = 0;

    std::vector<std::vector<bool>> currentGrid;
};