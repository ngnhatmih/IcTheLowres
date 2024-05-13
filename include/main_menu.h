#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "state.h"

class MainMenu: public State {
public:
    void update() override;
    void render() override;
    void clean() override;
};

#endif // MAIN_MENU_H