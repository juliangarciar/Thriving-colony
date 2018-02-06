#ifndef PANEL_H
#define PANEL_H

#include <nanogui/nanogui.h>
#include <GraphicEngine/Vector2.h>
#include "GUIElement.h"

class Panel : public GUIElement {

    public:
        Panel(std::string title);
        Panel(GUIElement *parent, std::string title);
        virtual ~Panel();

        void addChild(GUIElement *child);
        
        void setPosition(Vector2<int> position);
        void setTitle(std::string t);
        void setTooltip(std::string text);
        void setSize(Vector2<int> size);
        void setVerticalAlignment();
        void setGroupLayout();
        void setDragable(bool dragable);
        
        void show();
        void hide();

        void refreshLayout();

        void center();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Window *panel;
};

#endif