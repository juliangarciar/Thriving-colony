#include "Tab.h"
#include <GraphicEngine/Window.h>

Tab::Tab(nanogui::Widget *t){
    tab = t;
}

Tab::~Tab(){
    tab -> decRef();
}

void Tab::addChild(GUIElement *elem) {
    elem -> getGUIElement() -> setParent(tab);
    tab -> addChild(elem -> getGUIElement());
}

void Tab::setPosition(Vector2<i32> position){
    tab -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Tab::setTooltip(std::string text){
    tab -> setTooltip(text);
}

void Tab::show(){
    tab->setEnabled(true);
    tab -> setVisible(true);
}
 
void Tab::hide(){
    tab -> setVisible(false);
    tab->setEnabled(false);
}

bool Tab::isVisible(){
    return tab -> visible();
}

std::string Tab::getTitle(){
    return ""; //ToDo
}

nanogui::Widget *Tab::getGUIElement(){
    return tab;
}