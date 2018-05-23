#ifndef BUTTON_H
#define BUTTON_H

#include <nanogui/nanogui.h>
#include <Types.h>
#include <GUIEngine/GUIElement.h>
#include <MathEngine/Vector2.h>

class Button : public GUIElement{
    
    public:
        Button(std::string buttonText);
        Button(GUIElement *parent, std::string buttonText);
        virtual ~Button();

        void addChild(GUIElement *);

        void show();
        void hide();
        bool isVisible();

        bool isButtonPressed();
        void setButtonPressed(bool pressed);
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);

        void setTooltip(std::string text);
        void setText(std::string text);

        void setCallback(std::function<void()> callback);

        void refreshButton();
        void setBackgroundColor(i32 a, i32 r, i32 g, i32 b);

        void onHover();
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Button *button;
};

#endif