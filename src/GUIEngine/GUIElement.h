#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <irrlicht.h>

using namespace irr;

class GUIElement {
    public:
        virtual gui::IGUIElement *getGUIElement() = 0;
    private:
};

#endif