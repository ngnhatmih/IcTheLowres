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
            board[i][j].hovering = false;
        }
    }

    selected_cell = 0;

    TTF_Init();
    font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 60);
    if (font == nullptr) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
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
                    cell->hovering = true;
                    if (Game::getInstance().getInput()->getMouseButtonDown(MouseButtons::LEFT)) 
                        selected_cell = cell;

                } else {
                    cell->hovering = false;
                }
            }
        }
    }

    if (Game::getInstance().getInput()->getMouseButtonDown(MouseButtons::RIGHT)) {
        selected_cell = nullptr;
    }
}

void Grid::render() {
    // Paint grid background
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 22, 22, 22, 255);
    SDL_RenderFillRect(Game::getInstance().getRenderer(), &grid_rect);

    // Paint grid lines
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 44, 44, 44, 255);
    for (int x = grid_rect.x; x < grid_rect.x + grid_rect.w; x += cell_size) {
        SDL_RenderLine(Game::getInstance().getRenderer(), x, grid_rect.y, x, grid_rect.y + grid_rect.h);
    }

    for (int y = grid_rect.y; y < grid_rect.y + grid_rect.h; y += cell_size) {
        SDL_RenderLine(Game::getInstance().getRenderer(), grid_rect.x, y, grid_rect.x + grid_rect.w, y);
    }

    // Paint hovering cell
    Cell *tmp = hoveringCell();
    if (hovering && tmp != nullptr) {
        SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 255, 255, 255, 20); // why the alpha is not being alpha
        SDL_RenderFillRect(Game::getInstance().getRenderer(), &tmp->rect); // it should mix with the bg color right?
    }

    // green
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 0, 255, 0, 255);

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
            SDL_FRect text_rect = {cell->rect.x + cell->rect.w / 2 - 10, cell->rect.y + cell->rect.h / 2 - 10, 20, 20};
            if (sudoku->get_cell(i, j) != 0) {
                tmp_surf = TTF_RenderText_Solid(font, std::to_string(sudoku->get_cell(i, j)).c_str(), color);
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

Cell *Grid::hoveringCell() {
    for (int i = 0; i < sudoku->get_block_size() * sudoku->get_block_size(); i++) {
        for (int j = 0; j < sudoku->get_block_size() * sudoku->get_block_size(); j++) {
            Cell *cell = &board[i][j];
            if (cell->hovering) {
                return cell;
            }
        }
    }

    return nullptr;
}
