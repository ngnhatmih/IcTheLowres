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
            case SDL_EVENT_KEY_DOWN:
                onKeyDown(event);
                break;
            case SDL_EVENT_KEY_UP:
                onKeyUp(event);
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
            mouse_buttons[LEFT] = false;
            break;
        case SDL_BUTTON_MIDDLE:
            mouse_buttons[MIDDLE] = false;
            break;
        case SDL_BUTTON_RIGHT:
            mouse_buttons[RIGHT] = false;
            break;
        default:
            break;
    }
}

void Input::onKeyDown(SDL_Event &event)
{
    keystates = SDL_GetKeyboardState(0);
}

void Input::onKeyUp(SDL_Event &event)
{
    keystates = SDL_GetKeyboardState(0);
}


Input::Input()
{
    mouse_position = new Vector2D(0, 0);
    mouse_buttons.push_back(false);
    mouse_buttons.push_back(false);
    mouse_buttons.push_back(false);

    keystates = SDL_GetKeyboardState(0);
}

Input::~Input()
{
    delete mouse_position;
    mouse_buttons.clear();
}
