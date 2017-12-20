#ifndef TEXT_H
#define TEXT_H

#include <irrlicht.h>
#include "Rect2D.h"
#include "GUIElement.h"

class Text : public GUIElement {

    public:
        Text(Rect2D<int> dimPos, const wchar_t *text);
        ~Text();
        
        gui::IGUIElement *getGUIElement();
    private:
        gui::IGUIStaticText *text;
};

#endif