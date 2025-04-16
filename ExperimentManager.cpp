#include <iostream>

#include "ExperimentManager.h"
#include "PatternDetector.h"
#include "ConsoleUtils.h"
#include <thread>
#include <chrono>

ExperimentManager::ExperimentManager(const GameConfig& config) : config(config), grid(config) {}

bool ExperimentManager::RunExperiement() {
    int attemptCount = 0;
    int extraAttempts = 5;
    
    while (attemptCount < config.maxAttempts) {
        grid.SimulateAndDisplayStep(300);

        gridHistory.push_back(grid.GetCurrentGrid());

        if (PatternDetector::ContainsPattern(grid.GetCurrentGrid(), config.pattern)) {
            // Run extra iterations to check for stable pattern
            bool patternStable = true;
            for (int i = 0; i < extraAttempts; i++) {
                grid.SimulateAndDisplayStep(300);
                gridHistory.push_back(grid.GetCurrentGrid());

                if (!PatternDetector::ContainsPattern(grid.GetCurrentGrid(), config.pattern)) {
                    std::cout << config.pattern << " disappeared after " << (attemptCount + i + 1) << " steps.\n";
                    patternStable = false;
                    break;
                }
            }

            if (patternStable) {
                ClearConsole();
                std::cout << config.pattern << " found after " << attemptCount << " attempts and is stable!\n";
                std::cout << std::endl;
                std::cout << "Displaying all the steps (includes 5 extra steps) leading to the stable pattern: " << std::endl;
                
                // Display all the grids from start to the grid with stable pattern
                for (const auto& snapshot : gridHistory) {
                    std::cout << std::endl;
                    Grid::DisplayGrid(snapshot);
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
                return true;
            }
        }

        ++attemptCount;
    }

    std::cout << "Pattern not found after max attempts.\n";
    return false;
}