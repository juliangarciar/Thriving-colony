#ifndef BUTTON_H
#define BUTTON_H

#include <irrlicht.h>
#include <GraphicEngine/Rect.h>
#include <GraphicEngine/Vector3.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>

using namespace irr;

class Button {
    
    public:
        Button(Rect<int> dimPos, int id, const wchar_t *buttonText, const wchar_t *tooltipText);
        ~Button();

        bool isButtonPressed();
        void setIsPushButton(bool pushPresed);
        void setButtonPressed(bool pressed); 

    private:
        gui::IGUIButton *button;
};

#endif