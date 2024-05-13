#include "main_menu.h"
#include "game.h"
#include "play.h"

MainMenu::MainMenu() {
    play_button = 
    { // why this is able to do
        {(WINDOW_WIDTH-BUTTON_WIDTH)/2., (WINDOW_HEIGHT-BUTTON_HEIGHT)/2., BUTTON_WIDTH, BUTTON_HEIGHT}, // rect
        {22, 22, 22, 255}, // color
        false, // pressed
        false // hover
    };
}

MainMenu::~MainMenu() {
    
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
    } else {
        play_button.hover = false;
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

    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), play_button.color.r, play_button.color.g, play_button.color.b, play_button.color.a);
    SDL_RenderFillRect(Game::getInstance().getRenderer(), &play_button.rect);

    // dark grey background
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 44, 44, 44, 255);
}

void MainMenu::clean() {
    // Clean up the main menu
}