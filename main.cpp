#include <iostream>
#include "ConwaysGameOfLife.h"

int main()
{
    std::unique_ptr<ConwaysGameOfLife> game = std::make_unique<ConwaysGameOfLife>();

    game->MainMenu();
}
