#include "Widget.h"
#include <GraphicEngine/Window.h>

Widget::Widget() {
    widget = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Widget>();
    widget -> setFontSize(4);
}

Widget::Widget(GUIElement *parent) {
    widget = parent -> getGUIElement() -> add<nanogui::Widget>();
    parent -> addChild(this);
    widget -> setFontSize(4);
}

Widget::~Widget() {
    for (i32 i = 0; i < children.size(); i++){
        //if (children[i] -> getGUIElement() -> getRefCount() > 1) children[i] -> getGUIElement() -> decRef();
    }
    //ToDo: eliminar este
    hide();
}

void Widget::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void Widget::setPosition(Vector2<i32> position){
    widget -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Widget::setSize(Vector2<i32> size){
    widget -> setSize(Eigen::Vector2i(size.x, size.y));
}

void Widget::setTooltip(std::string t){
    widget -> setTooltip(t);
}

void Widget::setVerticalLayout() {
   widget -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 6));
}

void Widget::setGroupLayout() {
    widget -> setLayout(new nanogui::GroupLayout());
}

void Widget::show(){
    widget -> setVisible(true);
}
 
void Widget::hide(){
    widget -> setVisible(false);
}

bool Widget::isVisible(){
    return widget -> visible();
}

nanogui::Widget *Widget::getGUIElement(){
    return widget;
}