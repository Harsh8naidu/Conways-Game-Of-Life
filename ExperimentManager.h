#pragma once
#include <vector>

#include "Grid.h"
#include "GameConfig.h"

class ExperimentManager {
public:
    ExperimentManager(const GameConfig& config);
    bool RunExperiment();
    void LoadExperimentFromFile(const std::string& filename);
    void DisplayLoadedExperiment() const;

private:
    Grid grid;
    GameConfig config;
    std::vector<std::vector<std::vector<bool>>> gridHistory;

    void SaveExperimentToFile(const std::string& filename);
    void SerializeConfig(std::ofstream& outFile) const;
    void DeserializeConfig(std::ifstream& inFile);
};
