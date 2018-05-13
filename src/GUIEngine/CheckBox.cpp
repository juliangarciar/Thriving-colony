#include "CheckBox.h"
#include <GraphicEngine/Window.h>

CheckBox::CheckBox(std::string text) {
    checkbox = Window::Instance() -> getGUIEnvironment() -> add<nanogui::CheckBox>(text);
}

CheckBox::CheckBox(GUIElement *parent, std::string text) {
    checkbox = parent -> getGUIElement() -> add<nanogui::CheckBox>(text);
    parent->addChild(this);
}

CheckBox::~CheckBox() {
    for (i32 i = 0; i < children.size(); i++){
        //if (children[i] -> getGUIElement() -> getRefCount() > 1) children[i] -> getGUIElement() -> decRef();
    }
    //ToDo: eliminar este
    hide();
}

void CheckBox::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void CheckBox::show(){
    checkbox -> setVisible(true);
}
 
void CheckBox::hide(){
    checkbox -> setVisible(false);
}

bool CheckBox::isVisible(){
    return checkbox -> visible();
}

void CheckBox::setPosition(Vector2<i32> position){
    checkbox -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void CheckBox::setSize(Vector2<i32> size){
    checkbox -> setSize(Eigen::Vector2i(size.x, size.y));
}

void CheckBox::setTooltip(std::string text){
    checkbox -> setTooltip(text);
}

void CheckBox::setCallback(std::function<void(bool)> callback){
    checkbox -> setCallback(callback);
}

i32 CheckBox::isChecked(){
    return checkbox -> checked();
}

nanogui::Widget *CheckBox::getGUIElement(){
    return checkbox; 
}