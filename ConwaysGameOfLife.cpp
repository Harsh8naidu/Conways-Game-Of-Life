#include <iostream>

#include "ConwaysGameOfLife.h"

ConwaysGameOfLife::ConwaysGameOfLife()
{
    MainMenu();
}

void ConwaysGameOfLife::MainMenu()
{
    DisplayMenuOptions();
    int choice = GetMenuChoiceFromUser();
    HandleMenuChoice(choice);
}

void ConwaysGameOfLife::DisplayMenuOptions()
{
    std::cout << "Welcome to Conway's Game of Life" << std::endl;
    std::cout << std::endl;
    // Menu options
    std::cout << "1. Start a New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits" << std::endl;
    std::cout << "4. Exit Game" << std::endl;
}

int ConwaysGameOfLife::GetMenuChoiceFromUser()
{
    std::cout << std::endl;
    std::cout << "Enter an Input: ";
    int input;
    std::cin >> input;
    return input;
}

void ConwaysGameOfLife::HandleMenuChoice(int choice)
{
    switch (choice) {
    case 1:
        StartGame();
        break;
    case 2:
        LoadGame();
        break;
    case 3:
        Credits();
        break;
    case 4:
        ExitGame();
        break;
    default:
        std::cout << std::endl;
        std::cout << "Please enter a valid input!" << std::endl;
        int anotherChoice = GetMenuChoiceFromUser();
        HandleMenuChoice(anotherChoice);
    }
}

void ConwaysGameOfLife::StartGame()
{
    std::cout << std::endl;
    std::cout << "Starting Game..." << std::endl;
    config = GetGameSetupFromUser();
    grid = new Grid(config);
    grid->DisplayGrid();
    grid->RunSimulation();
}

void ConwaysGameOfLife::LoadGame()
{
}

void ConwaysGameOfLife::Credits()
{
}

void ConwaysGameOfLife::ExitGame()
{
    
}

GameConfig ConwaysGameOfLife::GetGameSetupFromUser()
{
    std::cout << "Enter number of rows: ";
    std::cin >> config.rows;

    std::cout << "Enter number of columns: ";
    std::cin >> config.columns;

    std::cout << "Enter number of alive cells: ";
    std::cin >> config.aliveCells;

    std::cout << "Enter number of steps: ";
    std::cin >> config.steps;

    return config;
}
