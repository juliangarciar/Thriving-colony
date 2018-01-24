#ifndef TEXT_H
#define TEXT_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"

class Text : public GUIElement {

    public:
        Text(std::string t);
        virtual ~Text();

        void setText(std::string t);
        
        void show();
        void hide();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Label *text;
};

#endif