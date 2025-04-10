#pragma once

class ConwaysGameOfLife {
public:
    ConwaysGameOfLife();
    ~ConwaysGameOfLife();

    void MainMenu();

protected:

    void DisplayMenuOptions();
    int GetMenuChoiceFromUser();
    void HandleMenuChoice(int choice);
};