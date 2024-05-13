#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "state.h"
#include "game.h"
#include "SDL3/SDL.h"

struct Button {
    SDL_FRect rect;
    SDL_Color color;
    bool pressed;
};

class MainMenu: public State {
public:
    MainMenu();
    ~MainMenu();
    void update() override;
    void render() override;
    void clean() override;

private:
    Button play_button;
};

#endif // MAIN_MENU_H