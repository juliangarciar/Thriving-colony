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

Tab *Panel::addTab(const wchar_t *text, int id){
    std::cout << ctrl << std::endl;
    gui::IGUITab *tab = ctrl->addTab(text, id);
    Tab *t = new Tab(tab);
    return t;
} 

Tab *Panel::getTab(int id){
    return new Tab(ctrl->getTab(id)); 
}

void Panel::enable(){
   ctrl->setEnabled(true);
   ctrl->setVisible(true);
}

void Panel::disable(){
   ctrl->setEnabled(false);
   ctrl->setVisible(false);
}

void Panel::changeActiveTab(int id){
   ctrl->setActiveTab(id);
}

gui::IGUITabControl *Panel::getTabControl(){
    return ctrl;
}
 