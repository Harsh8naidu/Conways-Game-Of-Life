#pragma once

#include "GameConfig.h"

class ConwaysGameOfLife {
public:
    ConwaysGameOfLife();
    ~ConwaysGameOfLife();

    void MainMenu();

protected:

    void DisplayMenuOptions();
    int GetMenuChoiceFromUser();
    void HandleMenuChoice(int choice);
    void StartGame();
    void LoadGame();
    void Credits();
    void ExitGame();
    GameConfig GetGameSetupFromUser();
};