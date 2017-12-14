#ifndef PANEL_H
#define PANEL_H

#include <irrlicht.h>
#include <GUIEngine/Rect2D.h>

using namespace irr;

class Panel {
    public:
        Panel(Rect2D<int> dimPos,  int id);
        ~Panel();

        gui::IGUITabControl *getTabControl();
    private:
        gui::IGUITabControl *ctrl;
};

#endif