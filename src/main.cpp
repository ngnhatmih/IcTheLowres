#include "sudoku.h"
#include "game.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Game &game = Game::getInstance();
    if(!game.init("ICTL", 800, 600))
    {
        SDL_Log("Failed to initialize game");
        return EXIT_FAILURE;
    }

    while(game.running())
    {
        game.handleEvents();
        game.update();
    }

    game.clean();

    return EXIT_SUCCESS;
}