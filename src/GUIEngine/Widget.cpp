#include "Widget.h"
#include <GraphicEngine/Window.h>

Widget::Widget() {
    widget = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Widget>();
}

Widget::Widget(GUIElement *parent) {
    widget = parent -> getGUIElement() -> add<nanogui::Widget>();
    parent->addChild(this);
}

Widget::~Widget() {
    for (int i = 0; i < children.size(); i++){
        //ToDo: eliminar hijos
    }
    //ToDo: eliminar este
    hide();

}

void Widget::addChild(GUIElement *elem) {
    children . push_back(elem);
}

void Widget::setPosition(Vector2<i32> position){
    widget -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Widget::setTooltip(std::string t){
    widget->setTooltip(t);
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