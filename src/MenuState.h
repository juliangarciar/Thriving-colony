#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "HudMenu.h"

class MenuState : public State {
    
    public:
        MenuState();
        virtual ~MenuState();

        void init();
        void input();
        void update();
        void render();
        void cleanUp();

    private:
        HudMenu * hud;

        int prevWindowWidth;
        int prevWindowHeight;
};

#endif