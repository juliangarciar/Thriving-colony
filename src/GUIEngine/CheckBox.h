#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <vector>
#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"

class CheckBox : public GUIElement {

    public:
        CheckBox(std::string text);
        CheckBox(GUIElement *parent, std::string text);
        virtual ~CheckBox();

        void show();
        void hide();

        int isChecked();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::CheckBox* checkbox;
};

#endif