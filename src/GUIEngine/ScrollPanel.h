#ifndef SCROLLPANEL_H
#define SCROLLPANEL_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"
#include <Types.h>

class ScrollPanel : public GUIElement {
    public:
        ScrollPanel();
        ScrollPanel(GUIElement *parent);
        virtual ~ScrollPanel();
        
        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);

        void setTooltip(std::string t);

        void setSize(Vector2<i32> size);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::VScrollPanel *spanel;
};

#endif