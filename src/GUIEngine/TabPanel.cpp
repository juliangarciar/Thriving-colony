#include "TabPanel.h"
#include <GraphicEngine/Window.h>

TabPanel::TabPanel(){
    ctrl = Window::Instance() -> getGUIEnvironment() -> add<nanogui::TabWidget>();
    ctrl ->setLayout(new nanogui::GroupLayout());
    tabs = new std::vector<Tab*>();
}

TabPanel::TabPanel(GUIElement *parent){
    ctrl = parent -> getGUIElement() -> add<nanogui::TabWidget>();
    ctrl ->setLayout(new nanogui::GroupLayout());
    tabs = new std::vector<Tab*>();
}

TabPanel::~TabPanel(){
    /*delete ctrl;
    ctrl = NULL;*/

    tabs -> clear();
    delete tabs;
}

Tab *TabPanel::createTab(std::string title){ 
    nanogui::Widget *layer = ctrl -> createTab(title);
    layer->setLayout(new nanogui::GroupLayout());

    Tab *t = new Tab(layer);
    tabs -> push_back(t);
    return t;
} 

Tab *TabPanel::getTab(int index){
    if (index < 0 || index > tabs->size()) return NULL; 
    else return tabs->at(index);
}

void TabPanel::changeActiveTab(int index){
    if (index >= 0) ctrl -> setActiveTab(index);
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

bool TabPanel::isVisible(){
    return ctrl -> visible();
}

nanogui::Widget *TabPanel::getGUIElement(){
    return ctrl;
}
 