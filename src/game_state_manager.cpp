#include "game_state_manager.h"

GameStateManager::GameStateManager() {}
GameStateManager::~GameStateManager() {}

void GameStateManager::pushState(GameState *state)
{
    states.push_back(state);
}

void GameStateManager::popState()
{
    states.pop_back();
}

void GameStateManager::changeState(GameState *state)
{
    if (!states.empty()) {
        popState();
    }
    pushState(state);
}

void GameStateManager::handleEvents()
{
    states.back()->handleEvents();
}

void GameStateManager::update()
{
    states.back()->update();
}

void GameStateManager::render()
{
    states.back()->render();
}