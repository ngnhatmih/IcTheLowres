#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50
#define TEXT_WIDTH 50
#define TEXT_HEIGHT 30

#include "state.h"
#include "SDL3_ttf/SDL_ttf.h"

struct Button {
    SDL_FRect rect;
    SDL_Color color;
    const char *text;
    SDL_Color text_color;
    SDL_FRect text_rect;
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
    TTF_Font *font;
};

#endif // MAIN_MENU_H