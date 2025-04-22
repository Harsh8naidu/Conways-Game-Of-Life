#pragma once
#include <vector>

#include "Grid.h"
#include "GameConfig.h"
#include "PauseController.h"

class ExperimentManager {
public:
    std::atomic<bool> isRunning = true;

    ExperimentManager(const GameConfig& config, PauseController* pauseController);
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

    PauseController* pauseController;
};
