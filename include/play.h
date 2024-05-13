#ifndef PLAY_H
#define PLAY_H

#include "state.h"

class Play: public State {
public:
    Play();
    ~Play();
    void update() override;
    void render() override;
    void clean() override;
};

#endif // PLAY_H