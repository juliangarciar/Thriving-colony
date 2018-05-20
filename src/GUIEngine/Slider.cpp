#include "Slider.h"

Slider::Slider(GUIElement *parent) {
    slider = Window::Instance() -> getGUIEnvironment() -> add<nanogui::Slider>();
    parent -> addChild(this);
}

Slider::~Slider() {
    for (i32 i = 0; i < children.size(); i++) {
        //if (children[i] -> getGUIElement() -> getRefCount() > 1) children[i] -> getGUIElement() -> decRef();
    }
    //ToDo: eliminar este
    hide();
}

void Slider::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void Slider::setPosition(Vector2<i32> position) {
    slider -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Slider::setTooltip(std::string t) {
    slider -> setTooltip(t);
}

void Slider::setRange(std::pair<f32,f32> r) {
    slider -> setRange(r);
}

void Slider::setSize(Vector2<i32> size) {
    slider -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

void Slider::show() {
    slider -> setVisible(true);
}
 
void Slider::hide() {
    slider -> setVisible(false);
}

bool Slider::isVisible() {
    return slider -> visible();
}

nanogui::Widget *Slider::getGUIElement() {
    return slider;
}