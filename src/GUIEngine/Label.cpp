#include "Label.h"
#include <GraphicEngine/Window.h>

Label::Label(std::string t) {
    label = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Label>(t);
}

Label::Label(GUIElement *parent, std::string t) {
    label = parent -> getGUIElement() -> add<nanogui::Label>(t);
    parent -> addChild(this);
}

Label::~Label() {
    for (i32 i = 0; i < children.size(); i++){
        //ToDo: eliminar hijos
    }
    //ToDo: eliminar este
    hide();
}

void Label::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void Label::setPosition(Vector2<i32> position){
    label -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Label::setTooltip(std::string t){
    label -> setTooltip(t);
}

void Label::setLabel(std::string t) {
    label -> setCaption(t);
}

void Label::setSize(Vector2<i32> size) {
    label -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

void Label::show(){
    label -> setVisible(true);
}
 
void Label::hide(){
    label -> setVisible(false);
}

void Label::setColor(i32 a, i32 r, i32 g, i32 b){
    label -> setColor(nanogui::Color(r, g, b, a));
}

bool Label::isVisible(){
    return label -> visible();
}

nanogui::Widget *Label::getGUIElement(){
    return label;
}