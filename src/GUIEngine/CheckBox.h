#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <vector>
#include <nanogui/nanogui.h>

#include <Types.h>
#include <GUIEngine/GUIElement.h>

class CheckBox : public GUIElement {

    public:
        CheckBox(std::string text);
        CheckBox(GUIElement *parent, std::string text);
        virtual ~CheckBox();

        void addChild(GUIElement *);

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);
        
        void setTooltip(std::string text);
        void setCallback(std::function<void(bool)> callback);

        i32 isChecked();
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::CheckBox* checkbox;
};

#endif