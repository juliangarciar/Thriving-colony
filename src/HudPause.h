#ifndef HUDPAUSE_H
#define HUDPAUSE_H

#include <GUIEngine/Button.h>

class HudPause {
    
    public:
        HudPause();
        ~HudPause();

        void setHUDEvents();

        void update();

    private:
        Button *buttonQuit;
        Button *buttonResume;
        Button *buttonMenu;
};

#endif