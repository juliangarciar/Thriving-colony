#include "TabPanel.h"
#include <GraphicEngine/Window.h>

TabPanel::TabPanel(){
    ctrl = Window::Instance() -> getGUIEnvironment() -> add<nanogui::TabWidget>();
    ctrl ->setLayout(new nanogui::GroupLayout());
    tabs = new std::map<int, Tab*>();
}

TabPanel::TabPanel(GUIElement *parent){
    ctrl = parent -> getGUIElement() -> add<nanogui::TabWidget>();
    ctrl ->setLayout(new nanogui::GroupLayout());
    tabs = new std::map<int, Tab*>();
}

TabPanel::~TabPanel(){
    /*delete ctrl;
    ctrl = NULL;*/

    tabs -> clear();
}

Tab *TabPanel::createTab(std::string title, int id){ 
    nanogui::Widget *layer = ctrl -> createTab(title);
    layer->setLayout(new nanogui::GroupLayout());

    Tab *t = new Tab(layer);
    tabs -> insert(std::pair<int, Tab*>(id, t));
    return t;
} 

Tab *TabPanel::getTab(int id){
    std::map<int,Tab*>::iterator it;
    it = tabs -> find(id);
    if (it != tabs -> end()) return tabs -> find(id) -> second;
    return NULL; 
}

void TabPanel::setPosition(Vector2<int> position){
    ctrl -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void TabPanel::setTooltip(std::string text){
    ctrl->setTooltip(text);
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

void TabPanel::refreshLayout(){
    Window::Instance()->getGUIEnvironment()->performLayout();
    ctrl->ensureTabVisible(ctrl->tabCount());
}

nanogui::Widget *TabPanel::getGUIElement(){
    return ctrl;
}
 