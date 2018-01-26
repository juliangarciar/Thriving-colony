#ifndef PANEL_H
#define PANEL_H

#include <nanogui/nanogui.h>
#include <GraphicEngine/Vector2.h>
#include "GUIElement.h"

class Panel : public GUIElement {

    public:
        Panel(std::string title);
        Panel(std::string title, Vector2<float> position);
        virtual ~Panel();

        void addChild(GUIElement *child);

        void setTitle(std::string t);
        
        void show();
        void hide();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Window *panel;
};

#endif