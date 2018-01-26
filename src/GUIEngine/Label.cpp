#include "Label.h"
#include <GraphicEngine/Window.h>

Label::Label(std::string t) {
    label = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Label>(t);
}

Label::~Label() {
    //ToDo: borrar Label
}

void Label::setPosition(Vector2<int> position){
    label -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Label::setTooltip(std::string t){
    label->setTooltip(t);
}

void Label::setLabel(std::string t) {
    label -> setCaption(t);
}

void Label::show(){
    label -> setVisible(true);
}
 
void Label::hide(){
    label -> setVisible(false);
}

nanogui::Widget *Label::getGUIElement(){
    return label;
}