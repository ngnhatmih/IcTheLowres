#ifndef GRID_H
#define GRID_H

#include "SDL3/SDL.h"
#include "sudoku.h"
#include "vector2d.h"

struct Cell {
    SDL_FRect rect;
    bool hovering;
    bool pressed;
};

class Grid {
public:
    Grid();
    ~Grid();
    Grid(int block_size, float cell_size);
    
    void update();
    void render();
    void clean();

    Cell *hoveringCell();

private:
    SDL_FRect grid_rect;
    Sudoku *sudoku;
    Cell **board;
    float cell_size;
    bool hovering;
    
};

#endif // GRID_H