#include "ScrollPanel.h"
#include <GraphicEngine/Window.h>

ScrollPanel::ScrollPanel() {
    spanel = Window::Instance() -> getGUIEnvironment() -> add<nanogui::VScrollPanel>();
}

ScrollPanel::ScrollPanel(GUIElement *parent) {
    spanel = parent -> getGUIElement() -> add<nanogui::VScrollPanel>();
    parent -> addChild(this);
}

ScrollPanel::~ScrollPanel() {
    for (i32 i = 0; i < children.size(); i++){
        //if (children[i] -> getGUIElement() -> getRefCount() > 1) children[i] -> getGUIElement() -> decRef();
    }
    //ToDo: eliminar este
    hide();
}

void ScrollPanel::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void ScrollPanel::setPosition(Vector2<i32> position){
    spanel -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void ScrollPanel::setTooltip(std::string t){
    spanel -> setTooltip(t);
}

void ScrollPanel::show(){
    spanel -> setVisible(true);
}
 
void ScrollPanel::hide(){
    spanel -> setVisible(false);
}

bool ScrollPanel::isVisible(){
    return spanel -> visible();
}

void ScrollPanel::setSize(Vector2<i32> size) {
    spanel -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

nanogui::Widget *ScrollPanel::getGUIElement(){
    return spanel;
}