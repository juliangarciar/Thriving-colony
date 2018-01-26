#include "CheckBox.h"
#include <GraphicEngine/Window.h>

CheckBox::CheckBox(std::string text) {
    checkbox = Window::Instance() -> getGUIEnvironment() -> add<nanogui::CheckBox>(text);
}

CheckBox::CheckBox(GUIElement *parent, std::string text) {
    checkbox = parent -> getGUIElement() -> add<nanogui::CheckBox>(text);
}

CheckBox::~CheckBox() {
    delete checkbox;
    checkbox = NULL;
}

void CheckBox::show(){
    checkbox -> setVisible(true);
}
 
void CheckBox::hide(){
    checkbox -> setVisible(false);
}

void CheckBox::setPosition(Vector2<int> position){
    checkbox -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void CheckBox::setTooltip(std::string text){
    checkbox -> setTooltip(text);
}

void CheckBox::setCallback(std::function<void(bool)> callback){
    checkbox -> setCallback(callback);
}

int CheckBox::isChecked(){
    return checkbox -> checked();
}

nanogui::Widget *CheckBox::getGUIElement(){
    return checkbox; 
}