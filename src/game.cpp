#include "game.h"

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

void Game::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
        {
            is_running = false;
        }
    }
}

void Game::update() {
    SDL_RenderClear(g_renderer);
    SDL_RenderPresent(g_renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

Game::~Game() {}