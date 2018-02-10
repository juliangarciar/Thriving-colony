#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <nanogui/nanogui.h>
#include "Rect2D.h"
#include "GUIElement.h"
#include <Types.h>

class TextBox : public GUIElement {
    public:
        TextBox(std::string t);
        TextBox(GUIElement *parent, std::string t);
        virtual ~TextBox();
        
        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);

        void setTooltip(std::string t);
        void setText(std::string t);
        void setEditable(bool b);

        void setSize(Vector2<i32> size);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::TextBox *textbox;
};

#endif