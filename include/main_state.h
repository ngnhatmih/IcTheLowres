#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include "game_state.h"

class MainState : public GameState {
public:
    MainState();
    ~MainState();
    void handleEvents() override;
    void update() override;
    void render() override;
};

#endif // MAIN_STATE_H