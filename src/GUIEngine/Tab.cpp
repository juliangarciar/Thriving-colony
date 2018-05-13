#include "Tab.h"
#include <GraphicEngine/Window.h>

Tab::Tab(nanogui::Widget *t){
    tab = t;
}

Tab::~Tab(){
    for (i32 i = 0; i < children.size(); i++){
        //if (children[i] -> getGUIElement() -> getRefCount() > 1) children[i] -> getGUIElement() -> decRef();
    }
    //ToDo: eliminar este
    hide();
}

void Tab::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void Tab::setPosition(Vector2<i32> position){
    tab -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Tab::setSize(Vector2<i32> size){
    tab -> setSize(Eigen::Vector2i(size.x, size.y));
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