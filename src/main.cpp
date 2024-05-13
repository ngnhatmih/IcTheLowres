#include "sudoku.h"
#include "game.h"
#include <iostream>

int main(int argc, char *argv[])
{   
    // create game instance
    Game &game = Game::getInstance();
    // create game window
    // exit if fail to create window
    if(!game.init("ICTL", 800, 600))
    {
        SDL_Log("Failed to initialize game");
        return EXIT_FAILURE;
    }

    // run game
    while(game.running())
    {
        game.render();
        game.handleEvents();
        game.update();
    }

    // exit game
    game.clean();

    return EXIT_SUCCESS;
}