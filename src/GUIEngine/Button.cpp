#include "Button.h"
#include <GraphicEngine/Window.h>

Button::Button(std::string buttonText) {
    button = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Button>(buttonText);
}

Button::Button(GUIElement *parent, std::string buttonText) {
    button = parent -> getGUIElement() -> add<nanogui::Button>(buttonText);
}

Button::~Button() {
    //delete button;
    this -> hide();
}

bool Button::isButtonPressed(){
    return button -> pushed();
}

void Button::setButtonPressed(bool pressed){
    button -> setPushed(pressed);
}

void Button::show(){
    button -> setVisible(true);
}
 
void Button::hide(){
    button -> setVisible(false);
}

void Button::setCallback(std::function<void()> callback){
    button -> setCallback(callback);
}

void Button::setTooltip(std::string text){
    button->setTooltip(text);
}

void Button::setText(std::string text){ 
    button -> setCaption(text);
}

void Button::setSize(Vector2<int> size){
    button -> setSize(Eigen::Vector2i(size.x, size.y));
}

void Button::setPosition(Vector2<int> position){
    button -> setPosition(Eigen::Vector2i(position.x, position.y));
}

nanogui::Widget *Button::getGUIElement(){
    return button; 
}