#include "CheckBox.h"
#include <GraphicEngine/Window.h>

CheckBox::CheckBox(std::string text) {
    checkbox = Window::Instance()->getGUIEnvironment()->add<nanogui::CheckBox>(text);
}

CheckBox::CheckBox(GUIElement *parent, std::string text) {
    checkbox = parent->getGUIElement()->add<nanogui::CheckBox>(text);
}

CheckBox::~CheckBox() {
    delete checkbox;
    checkbox = NULL;
}

void CheckBox::show(){
    checkbox->setVisible(true);
}
 
void CheckBox::hide(){
    checkbox->setVisible(false);
}

int CheckBox::isChecked(){
    return checkbox->checked();
}
 
nanogui::Widget *CheckBox::getGUIElement(){
    return checkbox; 
}