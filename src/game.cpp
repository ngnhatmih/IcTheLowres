#include "game.h"
#include "sudoku.h"
#include "input_handler.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

Game::Game() {
    g_window = nullptr;
    g_renderer = nullptr;
    is_running = true;
}

bool Game::init(const char *title, int width, int height) {
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) == 0)
    {
        g_window = SDL_CreateWindow(title, width, height, 0);
        if (g_window == nullptr)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s", SDL_GetError());
            return false;
        }
        else 
        {
            g_renderer = SDL_CreateRenderer(g_window, 0, 0);
        }
    }
    else { return false; }

    SDL_SetRenderDrawColor(g_renderer, 0, 20, 255, SDL_ALPHA_OPAQUE);
    return true;
}

void Game::render() {
    SDL_RenderClear(g_renderer);
    gsm->render();
    SDL_RenderPresent(g_renderer);
}

void Game::handleEvents() {
    InputHandler::getInstance().update();
}

void Game::update() {
    gsm->update();
}

void Game::clean() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

Game::~Game() {}