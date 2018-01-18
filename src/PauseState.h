#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"
#include "HudPause.h"

class PauseState : public State {
    
    public:
        PauseState();
        virtual ~PauseState();

        void init();
        void input();
        void update();
        void render();
        void cleanUp();

    private:
        HudPause * hud;

        int prevWindowWidth;
        int prevWindowHeight;
};

#endif