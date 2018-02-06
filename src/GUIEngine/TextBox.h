#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"

class TextBox : public GUIElement {
    public:
        TextBox(std::string t);
        TextBox(GUIElement *parent, std::string t);
        virtual ~TextBox();
        
        void setPosition(Vector2<int> position);

        void setTooltip(std::string t);
        void setText(std::string t);
        void setEditable(bool b);

        void setSize(Vector2<int> size);
        
        void show();
        void hide();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::TextBox *textbox;
};

#endif