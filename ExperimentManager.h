#pragma once
#include "Grid.h"
#include "GameConfig.h"

class ExperimentManager {
public:
    ExperimentManager(const GameConfig& config);
    bool RunExperiement();

private:
    Grid grid;
    GameConfig config;
};
