#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL3/SDL.h>
#include <vector>
#include "vector2d.h"

enum MouseButtons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};


class InputHandler {
public:
    static InputHandler &getInstance() {
        static InputHandler instance;
        return instance;
    }

    void onKeyDown(SDL_Event &event);
    void onKeyUp(SDL_Event &event);
    bool isKeyDown(SDL_Scancode key);

    void onMouseButtonDown(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);
    void onMouseMove(SDL_Event &event);
    bool getMouseButtonState(int button_number);
    Vector2D *getMousePosition();

    void update();
    void clean();

private:
    InputHandler();
    ~InputHandler();

    const Uint8 *keyboard_state;

    std::vector<bool> mouse_button_states;
    Vector2D *mouse_position;
};

#endif // INPUT_HANDLER_H