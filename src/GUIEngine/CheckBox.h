#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <vector>
#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"
#include <Types.h>

class CheckBox : public GUIElement {

    public:
        CheckBox(std::string text);
        CheckBox(GUIElement *parent, std::string text);
        virtual ~CheckBox();

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        
        void setTooltip(std::string text);
        void setCallback(std::function<void(bool)> callback);

        i32 isChecked();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::CheckBox* checkbox;
};

#endif