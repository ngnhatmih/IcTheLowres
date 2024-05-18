#ifndef GRID_H
#define GRID_H

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "sudoku.h"
#include "vector2d.h"

struct Cell {
    SDL_FRect rect;
    int col;
    int row;
    bool hovering;
    bool hidden;
};

class Grid {
public:
    Grid();
    ~Grid();
    Grid(int block_size, float cell_size);
    
    void update();
    void render();
    void clean();

private:
    SDL_FRect grid_rect;
    bool hovering;
    Sudoku *sudoku;

    Cell **board;
    Cell *selected_cell;
    Cell *hovering_cell;
    SDL_Color selected_border_color;
    float cell_size;

    TTF_Font *font;
};

#endif // GRID_H