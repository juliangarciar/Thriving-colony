#ifndef TABPANEL_H
#define TABPANEL_H

#include <irrlicht.h>
#include <vector>
#include <GUIEngine/Rect2D.h>
#include <GUIEngine/Tab.h>
#include "GUIElement.h"

using namespace irr;

class TabPanel : public GUIElement {
    public:
        TabPanel(Rect2D<int> dimPos,  int id);
        virtual ~TabPanel();

        Tab *addTab(const wchar_t *text, int id);
        Tab *getTab(int id);

        void enable();
        void disable();
        void changeActiveTab(int id);

        gui::IGUIElement *getGUIElement();
    private:
        gui::IGUITabControl *ctrl;
};

#endif