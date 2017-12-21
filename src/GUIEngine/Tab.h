#ifndef TAB_H
#define TAB_H

#include <irrlicht.h>
#include "GUIElement.h"

using namespace irr;

class Tab : public GUIElement{
    public:
        Tab(gui::IGUITab *tab);
        virtual ~Tab();

        void addChild(GUIElement *elem);

        const wchar_t *getText();
        int getID();

        gui::IGUIElement *getGUIElement();
    private:
        gui::IGUITab *tab;
};

#endif