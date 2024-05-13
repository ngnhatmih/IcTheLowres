#include "input.h"
#include "game.h"

void Input::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_EVENT_QUIT:
                Game::getInstance().setRunning(false);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                onMouseMove(event);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onMouseButtonDown(event);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonUp(event);
                break;
            default:
                break;
        }
    }
}

void Input::onMouseMove(SDL_Event &event)
{
    mouse_position->setX(event.motion.x);
    mouse_position->setY(event.motion.y);
}

void Input::onMouseButtonDown(SDL_Event &event)
{
    switch (event.button.button)
    {
        case SDL_BUTTON_LEFT:
            mouse_buttons[LEFT] = true;
            break;
        case SDL_BUTTON_MIDDLE:
            mouse_buttons[MIDDLE] = true;
            break;
        case SDL_BUTTON_RIGHT:
            mouse_buttons[RIGHT] = true;
            break;
        default:
            break;
    }
}

void Input::onMouseButtonUp(SDL_Event &event)
{
    switch (event.button.button)
    {
        case SDL_BUTTON_LEFT:
            mouse_buttons[LEFT] = true;
            break;
        case SDL_BUTTON_MIDDLE:
            mouse_buttons[MIDDLE] = true;
            break;
        case SDL_BUTTON_RIGHT:
            mouse_buttons[RIGHT] = true;
            break;
        default:
            break;
    }
}

Input::Input()
{
    mouse_position = new Vector2D(0, 0);
    mouse_buttons.push_back(false);
    mouse_buttons.push_back(false);
    mouse_buttons.push_back(false);
}

Input::~Input()
{
    delete mouse_position;
    mouse_buttons.clear();
}
