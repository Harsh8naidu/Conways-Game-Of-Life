#include "ConwaysGameOfLife.h"
#include <iostream>

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
        std::cout << "Starting Game..." << std::endl;
        break;
    case 2:
        std::cout << "Loading Game..." << std::endl;
        break;
    case 3:
        std::cout << "Credits..." << std::endl;
        break;
    case 4:
        std::cout << "Exiting Game..." << std::endl;
        break;
    default:
        std::cout << std::endl;
        std::cout << "Please enter a valid input!" << std::endl;
        int anotherChoice = GetMenuChoiceFromUser();
        HandleMenuChoice(anotherChoice);
    }
}
