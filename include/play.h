#ifndef PLAY_H
#define PLAY_H

#include "state.h"
#include "grid.h"

class Play: public State {
public:
    Play();
    ~Play();
    void update() override;
    void render() override;
    void clean() override;

private:
    Grid *grid;
};

#endif // PLAY_H