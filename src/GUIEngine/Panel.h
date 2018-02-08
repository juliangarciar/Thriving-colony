#ifndef PANEL_H
#define PANEL_H

#include <nanogui/nanogui.h>
#include <GraphicEngine/Vector2.h>
#include "GUIElement.h"
#include <Types.h>

class Panel : public GUIElement {

    public:
        Panel(std::string title);
        Panel(GUIElement *parent, std::string title);
        virtual ~Panel();
        
        void show();
        void hide();
        bool isVisible();

        void addChild(GUIElement *child);
        
        void setPosition(Vector2<i32> position);
        void setTitle(std::string t);
        void setTooltip(std::string text);
        void setSize(Vector2<i32> size);
        void setVerticalAlignment();
        void setGroupLayout();
        void setDragable(bool dragable);

        void refreshLayout();

        void center();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Window *panel;
};

#endif