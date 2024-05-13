#ifndef STATE_H
#define STATE_H

#include <SDL3/SDL.h>

class State {
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
};

#endif // STATE_H