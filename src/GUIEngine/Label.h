#ifndef LABEL_H
#define LABEL_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"

class Label : public GUIElement {

    public:
        Label(std::string t);
        virtual ~Label();
        
        void setPosition(Vector2<int> position);

        void setTooltip(std::string t);
        void setLabel(std::string t);
        
        void show();
        void hide();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Label *label;
};

#endif