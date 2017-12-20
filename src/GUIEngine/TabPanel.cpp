#include "TabPanel.h"
#include <GraphicEngine/Window.h>

using namespace irr;

TabPanel::TabPanel(Rect2D<int> dimPos, int id){
    Window *sc = Window::Instance();
    ctrl = sc->getGUIEnvironment()->addTabControl(dimPos.getRect2D(), 0, true, true, id);
}

TabPanel::~TabPanel(){
    delete ctrl;
    ctrl = NULL;
}

Tab *TabPanel::addTab(const wchar_t *text, int id){
    //std::cout << ctrl << std::endl;
    gui::IGUITab *tab = ctrl->addTab(text, id);
    Tab *t = new Tab(tab);
    return t;
} 

Tab *TabPanel::getTab(int id){
    return new Tab(ctrl->getTab(id)); 
}

void TabPanel::enable(){
   ctrl->setEnabled(true);
   ctrl->setVisible(true);
}

void TabPanel::disable(){
   ctrl->setEnabled(false);
   ctrl->setVisible(false);
}

void TabPanel::changeActiveTab(int id){
   ctrl->setActiveTab(id);
}

gui::IGUIElement *TabPanel::getGUIElement(){
    return ctrl;
}
 