#include <iostream>
#include <filesystem>

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
    std::string filename = AskUserForSaveFile();
    GameConfig config = DefaultGameConfig();
    ExperimentManager experiment(config);
    experiment.LoadExperimentFromFile(filename);
    experiment.DisplayLoadedExperiment();
}

void ConwaysGameOfLife::Credits()
{
}

void ConwaysGameOfLife::ExitGame()
{
    
}

GameConfig ConwaysGameOfLife::DefaultGameConfig()
{
    GameConfig defaultConfig;
    defaultConfig.rows = 10;
    defaultConfig.columns = 10;
    defaultConfig.aliveCells = 5;
    defaultConfig.steps = 1;
    defaultConfig.pattern = "";
    defaultConfig.maxAttempts = 10;

    return defaultConfig;
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

std::string ConwaysGameOfLife::AskUserForSaveFile() 
{
    // List all the save files in the Saves directory
    std::filesystem::path directoryPath = "Assets/Saves/";

    if (exists(directoryPath) && is_directory(directoryPath)) {
        std::cout << "\nSaved Experiments: \n" << std::endl;
        // Loop through each item/file in the directory
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    else {
        std::cerr << "Directory not found." << std::endl;
        return "";
    }

    std::string filename;
    std::cout << "\nPlease enter the name of the experiment you'd like to access: ";
    std::cin >> filename;
    std::cout << std::endl;

    std::filesystem::path fullPath = directoryPath / filename;
    return fullPath.string();
}
