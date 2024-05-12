#include "input_handler.h"
#include "game.h"

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                Game::getInstance().clean();
                break;
            case SDL_EVENT_KEY_DOWN:
                onKeyDown(event);
                break;
            case SDL_EVENT_KEY_UP:
                onKeyUp(event);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onMouseButtonDown(event);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonUp(event);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                onMouseMove(event);
                break;
            default:
                break;
        }
    }
}

void InputHandler::onKeyDown(SDL_Event &event)
{
    keyboard_state = SDL_GetKeyboardState(nullptr);
}

void InputHandler::onKeyUp(SDL_Event &event)
{
    keyboard_state = SDL_GetKeyboardState(nullptr);
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (keyboard_state != nullptr) {
        if (keyboard_state[key] == 1) {
            return true;
        }
    }
    return false;
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        mouse_button_states[LEFT] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        mouse_button_states[MIDDLE] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        mouse_button_states[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        mouse_button_states[LEFT] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        mouse_button_states[MIDDLE] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        mouse_button_states[RIGHT] = false;
    }
}

void InputHandler::onMouseMove(SDL_Event &event)
{
    mouse_position->setX(event.motion.x);
    mouse_position->setY(event.motion.y);
}

bool InputHandler::getMouseButtonState(int button_number)
{
    return mouse_button_states[button_number];
}

Vector2D *InputHandler::getMousePosition()
{
    return mouse_position;
}

void InputHandler::clean()
{
    
}

