#pragma once
#include <vector>

#include "Grid.h"
#include "GameConfig.h"

class ExperimentManager {
public:
    ExperimentManager(const GameConfig& config);
    bool RunExperiment();

private:
    Grid grid;
    GameConfig config;
    std::vector<std::vector<std::vector<bool>>> gridHistory;

    void SaveExperimentToFile(const std::string& filename);
};
