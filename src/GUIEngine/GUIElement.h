#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <nanogui/nanogui.h>

class GUIElement {
    public:
        virtual void show() = 0;
        virtual void hide() = 0;

        virtual nanogui::Widget *getGUIElement() = 0;
    private:
};

#endif