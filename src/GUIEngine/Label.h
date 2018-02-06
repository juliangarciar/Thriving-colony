#ifndef LABEL_H
#define LABEL_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"

class Label : public GUIElement {

    public:
        Label(std::string t);
        Label(GUIElement *parent, std::string t);
        virtual ~Label();

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<int> position);

        void setTooltip(std::string t);
        void setLabel(std::string t);

        void setSize(Vector2<int> size);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Label *label;
};

#endif