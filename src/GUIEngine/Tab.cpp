#include "Tab.h"
#include <GraphicEngine/Window.h>

/*Tab::Tab(TabPanel *parent, std::string title, int id){ 
    this->tab = parent->createTab(title, id)->getGUIElement();
}*/

Tab::Tab(nanogui::Widget *t){
    this->tab = t;
}

Tab::~Tab(){
    this->tab->decRef();
}

void Tab::addChild(GUIElement *elem){
    tab->addChild(elem->getGUIElement());
}

void Tab::show(){
    tab->setVisible(true);
}
 
void Tab::hide(){
    tab->setVisible(false);
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