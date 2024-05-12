#include "game_state_manager.h"

GameStateManager::GameStateManager() {}
GameStateManager::~GameStateManager() {}

void GameStateManager::pushState(GameState *state)
{
    states.push_back(state);
    states.back()->onEnter();
}

void GameStateManager::popState()
{
    if (!states.empty()) {
        if (states.back()->onExit()) {
            delete states.back();
            states.pop_back();
        }
    }
}

void GameStateManager::changeState(GameState *state)
{
    if (!states.empty()) {
        if (states.back()->onExit()) {
            delete states.back();
            states.pop_back();
        }
    }
    pushState(state);
    states.back()->onEnter();
}

void GameStateManager::update()
{
    if (!states.empty()) {
        states.back()->update();
    }
}

void GameStateManager::render()
{
    if (!states.empty()) {
        states.back()->render();
    }
}