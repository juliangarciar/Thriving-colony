#ifndef LISTBOX_H
#define LISTBOX_H

#include <vector>
#include <irrlicht.h>
#include "Rect2D.h"
#include "GUIElement.h"

class ListBox : public GUIElement {

    public:
        ListBox(Rect2D<int> dimPos);
        virtual ~ListBox();

        void addItem(const wchar_t *t);

        void removeItem(int id);
        void removeAllItems();

        int getSelected();
        
        gui::IGUIElement *getGUIElement();
        
    private:
        gui::IGUIListBox* listbox;
        //std::vector<float> *options;
};

#endif