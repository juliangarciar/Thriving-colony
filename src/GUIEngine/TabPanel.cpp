#include "TabPanel.h"
#include <GraphicEngine/Window.h>

TabPanel::TabPanel(){
    ctrl = Window::Instance() -> getGUIEnvironment() -> add<nanogui::TabWidget>();
    ctrl ->setLayout(new nanogui::GroupLayout());
}

TabPanel::TabPanel(GUIElement *parent){
    ctrl = parent -> getGUIElement() -> add<nanogui::TabWidget>();
    parent->addChild(this);
    ctrl ->setLayout(new nanogui::GroupLayout());
}

TabPanel::~TabPanel(){
    for (i32 i = 0; i < children.size(); i++){
        //ToDo: eliminar hijos
    }
    //ToDo: eliminar este
    hide();

    for (i32 i = 0; i < tabs.size(); i++){
        delete tabs.at(i);
    }
    tabs.clear();
}

void TabPanel::addChild(GUIElement *elem) {
    children.push_back(elem);
}

Tab *TabPanel::createTab(std::string title){ 
    nanogui::Widget *layer = ctrl -> createTab(title);
    layer->setLayout(new nanogui::GroupLayout());

    Tab *t = new Tab(layer);
    tabs.push_back(t);
    return t;
} 

Tab *TabPanel::getTab(i32 index){
    if (index < 0 || index > tabs.size()) return nullptr; 
    else return tabs.at(index);
}

void TabPanel::changeActiveTab(i32 index){
    if (index >= 0) ctrl -> setActiveTab(index);
}

void TabPanel::setPosition(Vector2<i32> position){
    ctrl -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void TabPanel::setSize(Vector2<i32> size){
    ctrl -> setSize(Eigen::Vector2i(size.x, size.y));
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
 