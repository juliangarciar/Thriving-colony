#ifndef WIDGET_H
#define WIDGET_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"

class Widget : public GUIElement {

    public:
        Widget();
        Widget(GUIElement *parent);
        virtual ~Widget();
        
        void setPosition(Vector2<int> position);
        void setTooltip(std::string text);

        void show();
        void hide();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Widget *widget;
};

#endif