#include "Tab.h"
#include <GraphicEngine/Window.h>

/*Tab::Tab(TabPanel *parent, std::string title, int id){ 
    this -> tab = parent -> createTab(title, id) -> getGUIElement();
}*/

Tab::Tab(nanogui::Widget *t){
    this -> tab = t;
}

Tab::~Tab(){
    this -> tab -> decRef();
}

void Tab::addChild(GUIElement *elem) {
    elem -> getGUIElement() -> setParent(tab);
    tab -> addChild(elem -> getGUIElement());
}

void Tab::setPosition(Vector2<int> position){
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

int Tab::getID(){
    return 0; //ToDo
}

nanogui::Widget *Tab::getGUIElement(){
    return tab;
}