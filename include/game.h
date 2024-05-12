#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>
#include "game_state_manager.h"

class Game {
public:
    static Game& getInstance() {
        static Game instance;                         
        return instance;
    }

    Game(Game const&) = delete;             
    void operator=(Game const&)  = delete;  
    
    bool init(const char *title, int width, int height);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running() { return is_running; }

    GameStateManager *getGameStateManager() { return gsm; }

private:
    Game();
    ~Game();

    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    bool is_running;

    GameStateManager *gsm;
};

#endif // GAME_H