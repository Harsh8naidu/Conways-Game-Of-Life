#pragma once

#include "Grid.h"

class ConwaysGameOfLife {
public:
    ConwaysGameOfLife();

    void MainMenu();
    void StartGame();
    void LoadGame();
    void Credits();
    void ExitGame();

    GameConfig DefaultGameConfig();

protected:
    GameConfig config;
    Grid* grid = nullptr;

    void DisplayMenuOptions();
    int GetMenuChoiceFromUser();
    void HandleMenuChoice(int choice);

    GameConfig GetGameSetupFromUser();
    std::string AskUserForSaveFile();
};