#ifndef LISTBOX_H
#define LISTBOX_H

#include <irrlicht.h>
#include "Rect2D.h"
#include "GUIElement.h"

class ListBox : public GUIElement {

    public:
        ListBox(Rect2D<int> dimPos);
        ~ListBox();

        void addItem(const wchar_t *t);
        
        gui::IGUIElement *getGUIElement();
    private:
        gui::IGUIListBox* listbox;
};

#endif