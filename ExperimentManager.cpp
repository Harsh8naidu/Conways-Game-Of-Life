#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>

#include "ExperimentManager.h"
#include "PatternDetector.h"
#include "ConsoleUtils.h"
#include "StringUtils.h";


ExperimentManager::ExperimentManager(const GameConfig& config) : config(config), grid(config) {}

bool ExperimentManager::RunExperiment() {
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
                    SaveExperimentToFile("Assets/Saves/" + ans);
                }
                
                return true;
            }
        }

        ++attemptCount;
    }

    std::cout << "Pattern not found after max attempts.\n";
    return false;
}

void ExperimentManager::SaveExperimentToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    // Save config data
    SerializeConfig(outFile);

    // Save grid history for the experiment
    for (const auto& snapshot : gridHistory) {
        for (const auto& row : snapshot) {
            for (bool cell : row) {
                char c = cell ? '1' : '0';
                outFile << c << " ";
            }
            outFile << "\n"; // End of row
        }
        outFile << "---\n"; // Separator between steps
    }

    std::cout << "\nSaved experiment to " << filename << "\n";
}

void ExperimentManager::LoadExperimentFromFile(const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Failed to load save!" << std::endl;
        return;
    }

    std::string str;
    std::vector<std::vector<bool>> snapshot;
    bool readingConfig = false;

    while (std::getline(inFile, str)) {
        Trim(str);

        if (str == "#CONFIG") {
            DeserializeConfig(inFile);
        } else if (str == "---") { // Separator between simulation steps
            gridHistory.push_back(snapshot);
            snapshot.clear();
        } else if (!str.empty() && (str.find('1') != std::string::npos || str.find('0') != std::string::npos)) {
            std::istringstream ss(str);
            std::vector<bool> row;
            char c;
            while (ss >> c) {
                // Convert character '1' and '0' into a bool with this little trick
                row.push_back(c == '1');
            }
            snapshot.push_back(row);
        }
    }

    // if file doesn't end with ---
    if (!snapshot.empty()) {
        gridHistory.push_back(snapshot);
    }

    std::cout << "Grid History size: " << gridHistory.size() << std::endl;
}

void ExperimentManager::SerializeConfig(std::ofstream& outFile) const {
    outFile << "#CONFIG\n";
    outFile << "rows: " << config.rows << "\n";
    outFile << "columns: " << config.columns << "\n";
    outFile << "aliveCells: " << config.aliveCells << "\n";
    outFile << "steps: " << config.steps << "\n";
    outFile << "pattern: " << config.pattern << "\n";
    outFile << "maxAttempts: " << config.maxAttempts << "\n";
    outFile << "#ENDCONFIG\n";
}

void ExperimentManager::DeserializeConfig(std::ifstream& inFile) {
    std::string str;
    while (std::getline(inFile, str)) {
        if (str == "#ENDCONFIG") break;

        std::istringstream iss(str);
        std::string key;
        if (std::getline(iss, key, ':')) { // ex: "row: 20"
            std::string value;
            std::getline(iss, value);
            value.erase(0, value.find_first_not_of(" \t")); // Trim leading whitespaces; ex: " 20" to "20"
            
            if (key == "rows") config.rows = std::stoi(value);
            else if (key == "columns") config.columns = std::stoi(value);
            else if (key == "aliveCells") config.aliveCells = std::stoi(value);
            else if (key == "steps") config.steps = std::stoi(value);
            else if (key == "pattern") config.pattern = value;
            else if (key == "maxAttempts") config.maxAttempts = std::stoi(value);
        }
    }

    // If needed later Grid can be created from the loaded config
    //grid = Grid(config);
}

void ExperimentManager::DisplayLoadedExperiment() const {
    std::cout << "Loaded Config:\n" << std::endl;
    std::cout << "Rows: " << config.rows << "\n";
    std::cout << "Columns: " << config.columns << "\n";
    std::cout << "Alive Cells: " << config.aliveCells << "\n";
    std::cout << "Steps: " << config.steps << "\n";
    std::cout << "Pattern: " << config.pattern << "\n";
    std::cout << "Max Attempts: " << config.maxAttempts << "\n";

    for (size_t step = 0; step < gridHistory.size(); step++) {
        std::cout << "\nStep " << step << ":\n" << std::endl;
        const auto& snapshot = gridHistory[step];
        for (const auto& row : snapshot) {
            for (bool cell : row) {
                std::cout << (cell ? '0' : '.');
            }
            std::cout << "\n";
        }
    }
}