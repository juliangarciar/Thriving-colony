#ifndef TAB_H
#define TAB_H

#include <irrlicht.h>
#include "Button.h"

using namespace irr;

class Tab {
    public:
        Tab(gui::IGUITab *tab);
        ~Tab();

        void addChild(Button *button);

        const wchar_t *getText();
        int getID();

        gui::IGUITab *getTab();
    private:
        gui::IGUITab *tab;
};

#endif