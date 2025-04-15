#include <iostream>

#include "ExperimentManager.h"
#include "PatternDetector.h"

ExperimentManager::ExperimentManager(const GameConfig& config) : config(config), grid(config) {}

bool ExperimentManager::RunExperiement() {
    int attemptCount = 0;
    int extraAttempts = 5;
    
    while (attemptCount < config.maxAttempts) {
        grid.SimulateAndDisplayStep(300);

        if (PatternDetector::ContainsPattern(grid.GetCurrentGrid(), config.pattern)) {
            // Run extra iterations to check for stable pattern
            bool patternStable = true;
            for (int i = 0; i < extraAttempts; i++) {
                grid.SimulateAndDisplayStep(300);
                if (!PatternDetector::ContainsPattern(grid.GetCurrentGrid(), config.pattern)) {
                    std::cout << config.pattern << " disappeared after " << (attemptCount + i + 1) << " steps.\n";
                    patternStable = false;
                    break;
                }
            }

            if (patternStable) {
                std::cout << config.pattern << " found after " << attemptCount << " attempts!\n";
                return true;
            }
            else {
                std::cout << config.pattern << " was found but not stable.\n";
            }
        }

        ++attemptCount;
    }

    std::cout << "Pattern not found after max attempts.\n";
    return false;
}