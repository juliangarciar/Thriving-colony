#ifndef WIDGET_H
#define WIDGET_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"
#include <Types.h>

class Widget : public GUIElement {

    public:
        Widget();
        Widget(GUIElement *parent);
        virtual ~Widget();

        void addChild(GUIElement *);

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);
        
        void setTooltip(std::string text);
        
        void setVerticalLayout();
        void setGroupLayout();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Widget *widget;
};

#endif