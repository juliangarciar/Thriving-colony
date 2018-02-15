#ifndef SCROLLPANEL_H
#define SCROLLPANEL_H

#include <nanogui/nanogui.h>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <GUIEngine/GUIElement.h>

class ScrollPanel : public GUIElement {
    public:
        ScrollPanel();
        ScrollPanel(GUIElement *parent);
        virtual ~ScrollPanel();

        void addChild(GUIElement *);
        
        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);

        void setTooltip(std::string t);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::VScrollPanel *spanel;
};

#endif