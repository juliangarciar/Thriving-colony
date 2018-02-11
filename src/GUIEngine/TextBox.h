#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <nanogui/nanogui.h>
#include <Types.h>
#include <GUIEngine/GUIElement.h>

class TextBox : public GUIElement {
    public:
        TextBox(std::string t);
        TextBox(GUIElement *parent, std::string t);
        virtual ~TextBox();

        void addChild(GUIElement *);
        
        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);

        void setTooltip(std::string t);
        void setText(std::string t);
        void setEditable(bool b);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::TextBox *textbox;
};

#endif