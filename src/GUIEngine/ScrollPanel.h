#ifndef SCROLLPANEL_H
#define SCROLLPANEL_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"

class ScrollPanel : public GUIElement {
    public:
        ScrollPanel();
        ScrollPanel(GUIElement *parent);
        virtual ~ScrollPanel();
        
        void setPosition(Vector2<int> position);

        void setTooltip(std::string t);

        void setSize(Vector2<int> size);
        
        void show();
        void hide();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::VScrollPanel *spanel;
};

#endif