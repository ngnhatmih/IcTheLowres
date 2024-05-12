#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <vector>
#include "game_state.h"

class GameStateManager {
public:
    static GameStateManager &getInstance() {
        static GameStateManager instance;
        return instance;
    }
    
    GameStateManager(GameStateManager const&) = delete;
    void operator=(GameStateManager const&) = delete;

    void pushState(GameState *state);
    void popState();
    void changeState(GameState *state);

    void handleEvents();
    void update();
    void render();
    
private:
    GameStateManager();
    ~GameStateManager();
    std::vector<GameState *> states;
};

#endif // GAME_STATE_MANAGER_H