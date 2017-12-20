#include "Tab.h"
#include <GraphicEngine/Window.h>

using namespace irr;

Tab::Tab(gui::IGUITab *tab){ 
    this->tab = tab;
}

Tab::~Tab(){
    delete tab;
    tab = NULL;
}

void Tab::addChild(GUIElement *elem){
    tab->addChild(elem->getGUIElement());
}

const wchar_t *Tab::getText(){
    return tab->getText();
}

int Tab::getID(){
    return tab->getID();
}

gui::IGUIElement *Tab::getGUIElement(){
    return tab;
}