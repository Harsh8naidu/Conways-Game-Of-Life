#pragma once
#include <thread>
#include <atomic>
#include <chrono>

#include "Grid.h"
#include "ExperimentManager.h"

class ConwaysGameOfLife {
public:
    ConwaysGameOfLife();
    ~ConwaysGameOfLife();

    void MainMenu();
    void StartGame();
    void LoadGame();
    void Credits();
    void ExitGame();

    GameConfig DefaultGameConfig();

protected:
    GameConfig config;
    Grid* grid = nullptr;
    ExperimentManager* experiment = nullptr;
    std::thread experimentThread;

    void DisplayMenuOptions();
    int GetMenuChoiceFromUser();
    void HandleMenuChoice(int choice);

    GameConfig GetGameSetupFromUser();
    std::string AskUserForSaveFile();
    void ListenForEscapeKey();
};