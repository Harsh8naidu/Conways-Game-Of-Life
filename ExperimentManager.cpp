#include <iostream>

#include "ExperimentManager.h"
#include "PatternDetector.h"

ExperimentManager::ExperimentManager(const GameConfig& config) : config(config), grid(config) {}

bool ExperimentManager::RunExperiement() {
    int attemptCount = 0;
    
    while (attemptCount < config.maxAttempts) {
        grid.SimulateAndDisplayStep(300);

        if (PatternDetector::ContainsPattern(grid.GetCurrentGrid(), config.pattern)) {
            std::cout << config.pattern << " found after " << attemptCount << "attempts!\n";
            return true;
        }

        ++attemptCount;
    }

    std::cout << "Pattern not found after max attempts.\n";
    return false;
}