#ifndef TEXT_H
#define TEXT_H

#include <irrlicht.h>
#include "Rect2D.h"
#include "GUIElement.h"

class Text : public GUIElement {

    public:
        Text(Rect2D<int> dimPos, const wchar_t *text);
        Text(Rect2D<int> dimPos, const wchar_t *text, bool bg);
        virtual ~Text();
        
        gui::IGUIElement *getGUIElement();
        void setText(const wchar_t *text);

        void disable();
        void enable();
    private:
        gui::IGUIStaticText *text;
};

#endif