#include "Button.h"
#include "Screen.h"

using namespace irr;

Button::Button(Rect<int> dimPos, int id, const wchar_t *buttonText, const wchar_t *tooltipText) {
    Screen *sc = Screen::Instance();
    std::cout<<dimPos<<std::endl;
    std::cout<<dimPos.getRect().getWidth()<<std::endl;
    std::cout<<dimPos.getRect().getHeight()<<std::endl;
    button = sc->getGUIEnvironment()->addButton(dimPos.getRect(), 0, id, buttonText, tooltipText);
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