#include "Button.h"
#include "Window.h"

using namespace irr;

Button::Button(Rect2D<int> dimPos, int id, const wchar_t *buttonText, const wchar_t *tooltipText) {
    Window *sc = Window::Instance();
    button = sc->getGUIEnvironment()->addButton(dimPos.getRect2D(), 0, id, buttonText, tooltipText);
}

bool Button::isButtonPressed(){
    return button->isPressed();
}

void Button::setIsPushButton(bool pushPresed){
    button->setIsPushButton(pushPresed);
}

void Button::setButtonPressed(bool pressed){
    button->setPressed(pressed);   
}

Button::~Button() {
    
}