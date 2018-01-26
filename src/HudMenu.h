#ifndef HUDMENU_H
#define HUDMENU_H

#include <GUIEngine/Button.h>

class HudMenu {
    
    public:
        HudMenu();
        ~HudMenu();

        void setHUDEvents();

        void update();

    private:
        Button *buttonQuit;
        Button *buttonStart;
};

#endif