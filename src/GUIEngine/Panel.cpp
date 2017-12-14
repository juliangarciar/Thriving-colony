#include "Panel.h"
#include <GraphicEngine/Window.h>

using namespace irr;

Panel::Panel(Rect2D<int> dimPos, int id){
    Window *sc = Window::Instance();
    ctrl = sc->getGUIEnvironment()->addTabControl(dimPos.getRect2D(), 0, true, true, id);
}

Panel::~Panel(){
    delete ctrl;
    ctrl = NULL;
}

gui::IGUITabControl *Panel::getTabControl(){
    return ctrl;
}

/*void Panel::addTab(Tab *tab){
    skin->addTab(tab->getText(), tab->getId());
} */