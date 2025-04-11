#pragma once

#include "Grid.h"

class ConwaysGameOfLife {
public:
    ConwaysGameOfLife();
    ~ConwaysGameOfLife();

    void MainMenu();
    void StartGame();
    void LoadGame();
    void Credits();
    void ExitGame();

protected:
    GameConfig config;
    Grid* grid = nullptr;

    void DisplayMenuOptions();
    int GetMenuChoiceFromUser();
    void HandleMenuChoice(int choice);

    GameConfig GetGameSetupFromUser();
};