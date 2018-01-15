#ifndef HUDMENU_H
#define HUDMENU_H

#include <GUIEngine/Button.h>

class HudMenu {
    
    public:
        HudMenu();
        ~HudMenu();

        void getHUDEvents();

        void update();
        void updatePositions();

    private:
        Button *buttonQuit;
        Button *buttonStart;
};

#endif