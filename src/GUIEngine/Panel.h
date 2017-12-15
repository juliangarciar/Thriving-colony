#ifndef PANEL_H
#define PANEL_H

#include <irrlicht.h>
#include <vector>
#include <GUIEngine/Rect2D.h>
#include <GUIEngine/Tab.h>

using namespace irr;

class Panel {
    public:
        Panel(Rect2D<int> dimPos,  int id);
        ~Panel();

        Tab *addTab(const wchar_t *text, int id);
        Tab *getTab(int id);

        void enable();
        void disable();
        void changeActiveTab(int id);

        gui::IGUITabControl *getTabControl();
    private:
        gui::IGUITabControl *ctrl;
};

#endif