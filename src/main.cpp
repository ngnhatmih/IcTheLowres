#include <iostream>
#include "game.cpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

using namespace std;

int main(int argc, char *argv[])
{
    Game &game = Game::getInstance();
    if(!game.init("ICTL", 800, 600))
    {
        cout << "Failed to initialize game" << endl;
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