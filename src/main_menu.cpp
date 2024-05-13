#include "main_menu.h"

MainMenu::MainMenu() {
    play_button = 
    { 
        {0., 0., 50., 50.}, // rect
        {22, 22, 22, 255}, // color
        false // pressed
    };
}

MainMenu::~MainMenu() {
    
}

void MainMenu::update() {
    // Update the main menu
}

void MainMenu::render() {
    // SDL_Surface *tmp = nullptr;
    // SDL_Texture *button_texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), tmp);
    // SDL_DestroySurface(tmp);
    
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), play_button.color.r, play_button.color.g, play_button.color.b, play_button.color.a);
    SDL_RenderFillRect(Game::getInstance().getRenderer(), &play_button.rect);
}

void MainMenu::clean() {
    // Clean up the main menu
}