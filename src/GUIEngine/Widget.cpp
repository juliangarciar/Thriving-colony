#include "Widget.h"
#include <GraphicEngine/Window.h>

Widget::Widget() {
    widget = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Widget>();
}

Widget::Widget(GUIElement *parent) {
    widget = parent -> getGUIElement() -> add<nanogui::Widget>();
}

Widget::~Widget() {
    //ToDo: borrar Widget
}

void Widget::setPosition(Vector2<int> position){
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

nanogui::Widget *Widget::getGUIElement(){
    return widget;
}