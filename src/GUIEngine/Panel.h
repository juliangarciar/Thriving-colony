#ifndef PANEL_H
#define PANEL_H

#include <nanogui/nanogui.h>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <GUIEngine/GUIElement.h>

class Panel : public GUIElement {

    public:
        Panel(std::string title);
        Panel(GUIElement *parent, std::string title);
        virtual ~Panel();

        void addChild(GUIElement *);
        
        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);

        void setTitle(std::string t);
        void setTooltip(std::string text);
        
        void setVerticalLayout();
        void setGroupLayout();

        void refreshLayout();

        void center();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Window *panel;
};

#endif