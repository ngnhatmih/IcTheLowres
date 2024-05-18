#include "grid.h"
#include "game.h"

Grid::Grid(int block_size, float cell_size) {
    sudoku = new Sudoku();
    sudoku->init(block_size);
    sudoku->solve();

    this->cell_size = cell_size;
    float grid_size = block_size * block_size * cell_size;
    grid_rect = {
        (WINDOW_WIDTH - grid_size) / 2.F,
        (WINDOW_HEIGHT - grid_size) / 2.F,
        grid_size,
        grid_size
    };

    board = new Cell*[block_size * block_size];
    for (int i = 0; i < block_size * block_size; i++) {
        board[i] = new Cell[block_size * block_size];
        for (int j = 0; j < block_size * block_size; j++) {
            board[i][j].rect = {
                grid_rect.x + j * cell_size,
                grid_rect.y + i * cell_size,
                cell_size,
                cell_size
            };
            board[i][j].col = j;
            board[i][j].row = i;
            board[i][j].hovering = false;
            board[i][j].hidden = false;
        }
    }

    for (int i = 0; i < block_size * block_size; i++) {
        for (int j = 0; j < block_size * block_size; j++) {
            if (rand() % 2 == 0) {
                board[i][j].hidden = true;
            }
        }
    }

    selected_cell = 0;
    hovering_cell = 0;

    TTF_Init();
    font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 60);
}

Grid::Grid() {

}


Grid::~Grid() {
    delete sudoku;
    
    for (int i = 0; i < sudoku->get_block_size() * sudoku->get_block_size(); i++) {
        delete[] board[i];
    }

    TTF_Quit();
}

void Grid::update() {
    if (Game::getInstance().getInput()->getMousePosition()->getX() > grid_rect.x &&
        Game::getInstance().getInput()->getMousePosition()->getX() < grid_rect.x + grid_rect.w &&
        Game::getInstance().getInput()->getMousePosition()->getY() > grid_rect.y &&
        Game::getInstance().getInput()->getMousePosition()->getY() < grid_rect.y + grid_rect.h) {
        hovering = true;
        
    } else {
        hovering = false;
    }

    if (hovering) {
        for (int i = 0; i < sudoku->get_block_size() * sudoku->get_block_size(); i++) {
            for (int j = 0; j < sudoku->get_block_size() * sudoku->get_block_size(); j++) {
                Cell *cell = &board[i][j];
                if (Game::getInstance().getInput()->getMousePosition()->getX() > cell->rect.x &&
                    Game::getInstance().getInput()->getMousePosition()->getX() < cell->rect.x + cell->rect.w &&
                    Game::getInstance().getInput()->getMousePosition()->getY() > cell->rect.y &&
                    Game::getInstance().getInput()->getMousePosition()->getY() < cell->rect.y + cell->rect.h) {
                    hovering_cell = cell;
                    if (Game::getInstance().getInput()->getMouseButtonDown(MouseButtons::LEFT)) 
                    {
                        selected_cell = cell;
                        selected_border_color = {0, 255, 0, 255};
                    }
                        
 
                }
            }
        }
    } else {
        hovering_cell = nullptr;
    }

    if (Game::getInstance().getInput()->getMouseButtonDown(MouseButtons::RIGHT)) {
        selected_cell = nullptr;
    }

    if (selected_cell != nullptr) {
        for (int i = 30; i < 39; i++) {
            if (Game::getInstance().getInput()->isKeyDown((SDL_Scancode) i)) {
                if (selected_cell->hidden) {
                    if (i - 29 == sudoku->get_cell(selected_cell->row, selected_cell->col)) {
                        selected_cell->hidden = false;
                        selected_border_color = {0, 255, 0, 255};
                    } else {
                        selected_border_color = {255, 0, 0, 255};
                    }
                }
            }
        }
    }
}

void Grid::render() {
    // Paint grid background
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 22, 22, 22, 255);
    SDL_RenderFillRect(Game::getInstance().getRenderer(), &grid_rect);

    // Draw grid lines
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 44, 44, 44, 255);
    for (int i = 0; i < sudoku->get_block_size() * sudoku->get_block_size(); i++) {
        SDL_RenderLine(Game::getInstance().getRenderer(), grid_rect.x + i * cell_size, grid_rect.y, grid_rect.x + i * cell_size, grid_rect.y + grid_rect.h);
    }

    for (int i = 0; i < sudoku->get_block_size() * sudoku->get_block_size(); i++) {
        SDL_RenderLine(Game::getInstance().getRenderer(), grid_rect.x, grid_rect.y + i * cell_size, grid_rect.x + grid_rect.w, grid_rect.y + i * cell_size);
    }
    
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 255, 255, 255, 255);
    for (int i = 1; i < sudoku->get_block_size(); i++) {
        SDL_RenderLine(Game::getInstance().getRenderer(), grid_rect.x + i * cell_size * sudoku->get_block_size(), grid_rect.y, grid_rect.x + i * cell_size * sudoku->get_block_size(), grid_rect.y + grid_rect.h);
    }

    for (int i = 1; i < sudoku->get_block_size(); i++) {
        SDL_RenderLine(Game::getInstance().getRenderer(), grid_rect.x, grid_rect.y + i * cell_size * sudoku->get_block_size(), grid_rect.x + grid_rect.w, grid_rect.y + i * cell_size * sudoku->get_block_size());
    }

    // Paint hovering cell
    if (hovering_cell != nullptr) {
        SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 255, 255, 255, 20); 
        SDL_RenderFillRect(Game::getInstance().getRenderer(), &hovering_cell->rect); 
    }

    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), selected_border_color.r, selected_border_color.g, selected_border_color.b, selected_border_color.a);

    // Draw selected cell border
    float offset = 2.f;
    if (selected_cell != nullptr) {
        // Left top corner
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x, selected_cell->rect.y, selected_cell->rect.x + offset, selected_cell->rect.y);
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x, selected_cell->rect.y, selected_cell->rect.x, selected_cell->rect.y + offset);

        // Right top corner
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x + selected_cell->rect.w - offset, selected_cell->rect.y, selected_cell->rect.x + selected_cell->rect.w, selected_cell->rect.y);
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x + selected_cell->rect.w, selected_cell->rect.y, selected_cell->rect.x + selected_cell->rect.w, selected_cell->rect.y + offset);

        // Left bottom corner
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x, selected_cell->rect.y + selected_cell->rect.h - offset, selected_cell->rect.x, selected_cell->rect.y + selected_cell->rect.h);
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x, selected_cell->rect.y + selected_cell->rect.h, selected_cell->rect.x + offset, selected_cell->rect.y + selected_cell->rect.h);

        // Right bottom corner
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x + selected_cell->rect.w - offset, selected_cell->rect.y + selected_cell->rect.h, selected_cell->rect.x + selected_cell->rect.w, selected_cell->rect.y + selected_cell->rect.h);
        SDL_RenderLine(Game::getInstance().getRenderer(), selected_cell->rect.x + selected_cell->rect.w, selected_cell->rect.y + selected_cell->rect.h - offset, selected_cell->rect.x + selected_cell->rect.w, selected_cell->rect.y + selected_cell->rect.h);
    }
    
    // Fill numbers to cells
    SDL_Color color = {255, 255, 255, 100};
    SDL_Surface *tmp_surf = nullptr;
    SDL_Texture *texture = nullptr;
    
    for (int i = 0; i < sudoku->get_block_size() * sudoku->get_block_size(); i++) {
        for (int j = 0; j < sudoku->get_block_size() * sudoku->get_block_size(); j++) {
            Cell *cell = &board[i][j];
            if (selected_cell != nullptr && sudoku->get_cell(i, j) == sudoku->get_cell(selected_cell->row, selected_cell->col) && !selected_cell->hidden) {
                color.a = 255;
            } else {
                color.a = 100;  
            }

            SDL_FRect text_rect = {cell->rect.x + cell->rect.w / 2 - 10, cell->rect.y + cell->rect.h / 2 - 10, 20, 20};
            if (!cell->hidden) {
                const char *num = "";
                if (sudoku->get_cell(i, j) < 10) {
                    num = std::to_string(sudoku->get_cell(i, j)).c_str();
                } else if (sudoku->get_cell(i, j) < 26){
                    char c = 'A' + sudoku->get_cell(i, j) - 10;
                    num = &c;
                }
                tmp_surf = TTF_RenderText_Solid(font, num, color);
                texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), tmp_surf);
                SDL_RenderTexture(Game::getInstance().getRenderer(), texture, nullptr, &text_rect);
                SDL_DestroySurface(tmp_surf);
                SDL_DestroyTexture(texture);
            }
        }
    }
}

void Grid::clean() {

}
