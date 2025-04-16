#include <iostream>

#include "ConwaysGameOfLife.h"
#include "PatternDetector.h"
#include "ExperimentManager.h"

ConwaysGameOfLife::ConwaysGameOfLife()
{
    
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
    
    if (!config.pattern.empty()) {
        ExperimentManager experiment(config);
        experiment.RunExperiment();
        return;
    }

    grid = new Grid(config);
    grid->DisplayGrid();
    std::cout << std::endl;
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
    GameConfig gameConfig;

    std::string ans;
    std::cout << "Do you want to search for a pattern? (y/n): ";
    std::cin >> ans;

    if (ans == "y") {
        std::vector<std::string> patterns = PatternDetector::GetAvailablePatterns();

        std::cout << "Available patterns are: " << std::endl;
        for (const auto& p : patterns) {
            std::cout << "> " << p << " " << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Enter the name of the pattern: ";
        std::cin >> gameConfig.pattern;

        // check if the pattern is valid and exists
        bool isValid = std::find(patterns.begin(), patterns.end(), gameConfig.pattern) != patterns.end();

        while (!isValid) {
            std::cout << "Invalid pattern. Please enter a valid pattern name: ";
            std::cin >> gameConfig.pattern;
            isValid = std::find(patterns.begin(), patterns.end(), gameConfig.pattern) != patterns.end();
        }

        std::cout << "Please enter the number of experiments you'd like to run: ";
        std::cin >> gameConfig.maxAttempts;
    }

    std::cout << "Enter number of rows: ";
    std::cin >> gameConfig.rows;

    std::cout << "Enter number of columns: ";
    std::cin >> gameConfig.columns;

    std::cout << "Enter number of alive cells: ";
    std::cin >> gameConfig.aliveCells;

    if (ans != "y") {
        std::cout << "Enter number of steps: ";
        std::cin >> gameConfig.steps;
    }

    return gameConfig;
}
