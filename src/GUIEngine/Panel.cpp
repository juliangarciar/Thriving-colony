#include "Panel.h"
#include <GraphicEngine/Window.h>
#include <nanogui/layout.h>

Panel::Panel(std::string t) {
    panel = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Window>(t);
    panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
}

Panel::Panel(std::string t, Vector2<float> position) {
    panel = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Window>(t);
    panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
    panel -> setPosition(Eigen::Vector2i(position.x, position.y));
}

Panel::~Panel() {
    
}

void Panel::addChild(GUIElement *child){
    panel -> addChild(child -> getGUIElement());
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

nanogui::Widget *Panel::getGUIElement(){
    return panel;
}