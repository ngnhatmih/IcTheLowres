#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 15

#include "state.h"
#include "game.h"

struct Button {
    SDL_FRect rect;
    SDL_Color color;
    bool pressed;
    bool hover;
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