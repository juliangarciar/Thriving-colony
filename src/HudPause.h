#ifndef HUDPAUSE_H
#define HUDPAUSE_H

#include <GUIEngine/Button.h>

class HudPause {
    
    public:
        HudPause();
        ~HudPause();

        void getHUDEvents();

        void update();
        void updatePositions();

    private:
        Button *buttonQuit;
        Button *buttonResume;
        Button *buttonMenu;
};

#endif