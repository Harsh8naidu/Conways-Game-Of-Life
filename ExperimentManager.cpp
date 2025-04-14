#include <iostream>

#include "ExperimentManager.h"
#include "PatternDetector.h"

ExperimentManager::ExperimentManager(const GameConfig& config) : config(config), grid(config) {}

bool ExperimentManager::RunExperiement() {
    int attemptCourt = 0;
    
    while (attemptCourt < config.maxAttempts) {
        grid.RunSimulation();

        if (PatternDetector::ContainsPattern(grid.GetCurrentGrid(), config.pattern)) {
            std::cout << "Pattern found after " << attemptCourt << "attempts!\n";
            grid.DisplayGrid();
            return true;
        }

        ++attemptCourt;
    }

    std::cout << "Pattern not found after max attempts.\n";
    return false;
}