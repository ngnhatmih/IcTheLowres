#include "game.h"

Game::Game() {
    g_window = nullptr;
    g_renderer = nullptr;
    is_running = true;
    input = nullptr;
    current_state = nullptr;
}

bool Game::init(const char *title, int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_CAMERA | SDL_INIT_TIMER) == 0)
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
    input = new Input();
    current_state = new MainMenu();
    return true;
}

void Game::render() {
    SDL_RenderClear(g_renderer);
    current_state->render();
    SDL_RenderPresent(g_renderer);
}

void Game::handleEvents() {
    input->update();
}

void Game::update() {
    current_state->update();
}

void Game::clean() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

Game::~Game() {}