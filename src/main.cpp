#include "game.cpp"
#include "sudoku.cpp"

int main(int argc, char *argv[])
{
    // Game &game = Game::getInstance();
    // if(!game.init("ICTL", 800, 600))
    // {
    //     cout << "Failed to initialize game" << endl;
    //     return EXIT_FAILURE;
    // }

    // while(game.running())
    // {
    //     game.handleEvents();
    //     game.update();
    // }

    // game.clean();

    Sudoku &sudoku = Sudoku::getInstance();
    sudoku.init(4);
    sudoku.solve();
    sudoku.display();
    sudoku.clear();
    sudoku.display();
    return EXIT_SUCCESS;
}