#include "main_menu.h"
#include "game.h"
#include "play.h"

MainMenu::MainMenu() {
    TTF_Init();
    font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 60);

    
    play_button = 
    { 
        {(WINDOW_WIDTH-BUTTON_WIDTH)/2., (WINDOW_HEIGHT-BUTTON_HEIGHT)/2., BUTTON_WIDTH, BUTTON_HEIGHT}, // rect
        {22, 22, 22, 255}, // color
        "PLAY", // text
        {225, 225, 225, 225}, // text color
        {(WINDOW_WIDTH-TEXT_WIDTH)/2. , (WINDOW_HEIGHT-TEXT_HEIGHT)/2., TEXT_WIDTH, TEXT_HEIGHT},
        false, // pressed
        false // hover
    };
}

MainMenu::~MainMenu() {
    TTF_Quit();
}

void MainMenu::update() {
    // press button and wait to release
    if (play_button.pressed && !Game::getInstance().getInput()->getMouseButtonDown(MouseButtons::LEFT)) {
        Game::getInstance().changeState(new Play());
    }

    // detect hovering
    Vector2D *pos = Game::getInstance().getInput()->getMousePosition();
    if (pos->getX() > play_button.rect.x && pos->getX() < play_button.rect.x + play_button.rect.w &&
        pos->getY() > play_button.rect.y && pos->getY() < play_button.rect.y + play_button.rect.h) {
        play_button.hover = true;
        play_button.text_color = {0, 0, 0, 255};
    } else {
        play_button.hover = false;
        play_button.text_color = {225, 225, 225, 225};
    }

    // detect pressing
    if (play_button.hover && Game::getInstance().getInput()->getMouseButtonDown(MouseButtons::LEFT)) {
        play_button.pressed = true;
    } else {
        play_button.pressed = false;
    }

    // change color based on hover and press
    if (play_button.hover) {
        if (play_button.pressed) {
            // green
            play_button.color = {0, 255, 0, 255};
            play_button.text_color = {225, 225, 225, 255};
        } else {
            play_button.color = {255, 255, 255, 255};
        }
    } else {
        play_button.color = {22, 22, 22, 255};
    }

}

void MainMenu::render() {
    // SDL_Surface *tmp = nullptr;
    // SDL_Texture *button_texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), tmp);
    // SDL_DestroySurface(tmp);

    // draw play button
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), play_button.color.r, play_button.color.g, play_button.color.b, play_button.color.a);
    SDL_RenderFillRect(Game::getInstance().getRenderer(), &play_button.rect);

    // draw text
    SDL_Surface *tmp = TTF_RenderText_Solid(font, play_button.text, play_button.text_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), tmp);
    SDL_RenderTexture(Game::getInstance().getRenderer(), texture, 0, &play_button.text_rect);
    SDL_DestroySurface(tmp);

    // dark grey background
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 44, 44, 44, 255);
}

void MainMenu::clean() {
    // Clean up the main menu
    
}