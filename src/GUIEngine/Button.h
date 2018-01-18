#ifndef BUTTON_H
#define BUTTON_H

#include <irrlicht.h>
#include <GUIEngine/Rect2D.h>
//#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>
#include "GUIElement.h"

using namespace irr;

class Button : public GUIElement{
    
    public:
        Button(Rect2D<int> dimPos, int id, const wchar_t *buttonText, const wchar_t *tooltipText);
        virtual ~Button();

        bool isButtonPressed();
        void setIsPushButton(bool pushPresed);
        void setButtonPressed(bool pressed); 

        void setText(const wchar_t* text);
        void setPosition(Vector2<int> pos);

        gui::IGUIElement *getGUIElement();

    private:
        gui::IGUIButton *button;
};

#endif