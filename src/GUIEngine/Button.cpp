#include "Button.h"
#include <GraphicEngine/Window.h>

Button::Button(std::string buttonText) {
    button = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Button>(buttonText);
    button -> setFontSize(16);
}

Button::Button(GUIElement *parent, std::string buttonText) {
    button = parent -> getGUIElement() -> add<nanogui::Button>(buttonText);
    parent -> addChild(this);
    button -> setFontSize(16);
}

Button::~Button() {
    for (i32 i = 0; i < children.size(); i++) {
        //if (children[i] != nullptr && children[i] -> getGUIElement() != nullptr) delete children[i];
    }
    //ToDo: eliminar este
    hide();
}

void Button::addChild(GUIElement *elem) {
    children.push_back(elem);
}

bool Button::isButtonPressed() {
    return button -> pushed();
}

void Button::setButtonPressed(bool pressed) {
    button -> setPushed(pressed);
}

void Button::show() {
    button -> setVisible(true);
}
 
void Button::hide() {
    button -> setVisible(false);
}

bool Button::isVisible() {
    return button -> visible();
}

void Button::setCallback(std::function<void()> callback) {
    button -> setCallback(callback);
}

void Button::setTooltip(std::string text) {
    button->setTooltip(text);
}

void Button::setText(std::string text) { 
    button -> setCaption(text);
}

void Button::setSize(Vector2<i32> size) {
    //button -> setSize(Eigen::Vector2i(size.x, size.y));
    button-> setFixedSize(nanogui::Vector2i(size.x, size.y));
}

void Button::setPosition(Vector2<i32> position) {
    button -> setPosition(Eigen::Vector2i(position.x, position.y));
}
void Button::refreshButton() {
    //button-> setFixedSize(nanogui::Vector2i(300, 200));
}
void Button::setBackgroundColor(i32 a, i32 r, i32 g, i32 b) {
    button -> setBackgroundColor(nanogui::Color(r, g, b, a));
}
nanogui::Widget *Button::getGUIElement() {
    return button; 
}

void Button::onHover(){
    if(button->focused()){
        std::cout << "Ye primi \n";
    }
}
