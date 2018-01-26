#include "Panel.h"
#include <GraphicEngine/Window.h>
#include <nanogui/layout.h>

Panel::Panel(std::string t) {
    //panel = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Window>(t);
    panel = new nanogui::Window(Window::Instance() -> getGUIEnvironment(), t);
    panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
}

Panel::Panel(std::string t, Vector2<float> position) {
   // panel = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Window>(t);
    panel = new nanogui::Window(Window::Instance() -> getGUIEnvironment(), t);
    panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
    panel -> setPosition(Eigen::Vector2i(position.x, position.y));
}

Panel::Panel(GUIElement *parent, std::string title) {
    panel = new nanogui::Window(parent -> getGUIElement(), title);
    panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
    
}

Panel::~Panel() {
    delete panel;
}

void Panel::addChild(GUIElement *child){
    panel -> addChild(child -> getGUIElement());
}

void Panel::setPosition(Vector2<int> position){
    panel -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Panel::setTooltip(std::string text){
    panel->setTooltip(text);
}

void Panel::setTitle(std::string t) {
    panel -> setTitle(t);
}

void Panel::show(){
    panel -> setVisible(true);
}
 
void Panel::hide(){
    panel -> setVisible(false);
}

void Panel::center(){
    panel -> center();
}

void Panel::setVerticalAlignment() {
   panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 6));
}

void Panel::setSize(Vector2<int> size) {
    panel -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

void Panel::setGroupLayout() {
    panel -> setLayout(new nanogui::GroupLayout());
}

nanogui::Widget *Panel::getGUIElement(){
    return panel;
}
