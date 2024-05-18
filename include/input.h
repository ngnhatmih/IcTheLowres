#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <vector>
#include "vector2d.h"

enum MouseButtons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class Input {
public:
    Input();
    ~Input();

    void update();

    // mouse
    void onMouseMove(SDL_Event &event);
    void onMouseButtonDown(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);
    Vector2D *getMousePosition() { return mouse_position; }
    bool getMouseButtonDown(MouseButtons button) { return mouse_buttons[button]; }

    // keyboard
    void onKeyDown(SDL_Event &event);
    void onKeyUp(SDL_Event &event);
    bool isKeyDown(SDL_Scancode key) { return keystates[key]; }

private:
    // mouse
    Vector2D *mouse_position;
    std::vector<bool> mouse_buttons;

    // keyboard
    const Uint8 *keystates;

};

#endif // INPUT_H