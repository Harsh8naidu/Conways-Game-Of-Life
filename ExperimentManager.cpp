#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>

#include "ExperimentManager.h"
#include "PatternDetector.h"
#include "ConsoleUtils.h"


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
                
                int stepNumber = 0;
                // Display all the grids from start to the grid with stable pattern
                for (const auto& snapshot : gridHistory) {
                    std::cout << std::endl;
                    std::cout << "Step: " << stepNumber << std::endl;
                    Grid::DisplayGrid(snapshot);
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    stepNumber++;
                }

                std::cout << std::endl;
                std::string ans;
                std::cout << "Do you want to save this experiement? (y/n): ";
                std::cin >> ans;
                if (ans == "y") {
                    std::cout << std::endl;
                    std::cout << "Enter the filename to save the file as: ";
                    std::cin >> ans;
                    // Create and write the grid history to a file
                    if (ans.size() < 4 || ans.substr(ans.size() - 4) != ".txt") {
                        ans += ".txt";
                    }
                    SaveHistoryToFile(ans);
                }
                
                return true;
            }
        }

        ++attemptCount;
    }

    std::cout << "Pattern not found after max attempts.\n";
    return false;
}

void ExperimentManager::SaveHistoryToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    for (const auto& snapshot : gridHistory) {
        for (const auto& row : snapshot) {
            for (bool cell : row) {
                char c = cell ? '1' : '0';
                outFile << c << " ";
                outFile.write(&c, sizeof(char));
            }
            outFile << "\n"; // End of row
        }
        outFile << "---\n"; // Separator between steps
    }

    std::cout << std::endl;
    std::cout << "Saved experiment to " << filename << "\n";
}