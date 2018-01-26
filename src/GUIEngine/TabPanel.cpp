#include "TabPanel.h"
#include <GraphicEngine/Window.h>

TabPanel::TabPanel(){
    ctrl = Window::Instance() -> getGUIEnvironment() -> add<nanogui::TabWidget>();
    //addTabControl(dimPos.getRect2D(), 0, true, true, id);

    tabs = new std::map<int, Tab*>();
}

TabPanel::~TabPanel(){
    /*delete ctrl;
    ctrl = NULL;*/

    tabs -> clear();
}

Tab *TabPanel::createTab(std::string text, int id){ 
    Tab *t = new Tab(ctrl -> createTab(id, text));
    tabs -> insert(std::pair<int, Tab*>(id, t));
    return t;
} 

Tab *TabPanel::getTab(int id){
    std::map<int,Tab*>::iterator it;
    it = tabs -> find(id);
    if (it != tabs -> end()) return tabs -> find(id) -> second;
    return NULL; 
}

void TabPanel::show(){
    ctrl -> setVisible(true);
}
 
void TabPanel::hide(){
    ctrl -> setVisible(false);
}

bool TabPanel::changeActiveTab(int id){
    std::map<int,Tab*>::iterator it = tabs -> find(id);
    if (it != tabs -> end()) {
        ctrl -> setActiveTab(id);
        return true;
    }
    return false;
}

nanogui::Widget *TabPanel::getGUIElement(){
    return ctrl;
}
 