#ifndef BUTTON_H
#define BUTTON_H

#include <nanogui/nanogui.h>
#include <GraphicEngine/Vector2.h>
#include "GUIElement.h"

class Button : public GUIElement{
    
    public:
        Button(std::string buttonText);
        Button(GUIElement *parent, std::string buttonText);
        virtual ~Button();

        bool isButtonPressed();
        void setButtonPressed(bool pressed);

        void show();
        void hide();

        void setText(std::string text);
        void setSize(Vector2<int> size);
        void setPosition(Vector2<int> position);
        void setButtonCallback(std::function<void()> callback);

        nanogui::Widget *getGUIElement();
    private:
        nanogui::Button *button;
};

#endif