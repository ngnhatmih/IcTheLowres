#include "play.h"
#include "game.h"

Play::Play() {
    grid = new Grid(3, 50);
    SDL_SetRenderDrawBlendMode(Game::getInstance().getRenderer(), SDL_BLENDMODE_BLEND);
}

Play::~Play() {
    delete grid;
}

void Play::update() {
    grid->update();
}

void Play::render() {
    grid->render();
    SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 255, 255, 255, 255);
    
}

void Play::clean() {
    grid->clean();
}

