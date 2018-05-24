#include "Panel.h"
#include <GraphicEngine/Window.h>
#include <nanogui/layout.h>

Panel::Panel(std::string t) {
    panel = new nanogui::Window(Window::Instance() -> getGUIEnvironment(), t);
    panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
    panel -> setModal(false);
    panel -> setFontSize(1);
    //panel -> transpa
}

Panel::Panel(GUIElement *parent, std::string title) {
    panel = new nanogui::Window(parent -> getGUIElement(), title);
    parent -> addChild(this);
    panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
    panel -> setFontSize(1);
}

Panel::~Panel() {
    for (i32 i = 0; i < children.size(); i++) {
        //if (children[i] != nullptr && children[i] -> getGUIElement() -> getRefCount() > 1) children[i] -> getGUIElement() -> decRef();
    }
    //ToDo: eliminar este
    hide();
}

void Panel::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void Panel::show() {
    panel -> setVisible(true);
}
 
void Panel::hide() {
    panel -> setVisible(false);
}

bool Panel::isVisible() {
    return panel -> visible();
}

void Panel::center() {
    panel -> center();
}

void Panel::refreshLayout() {
    Window::Instance()->getGUIEnvironment()->performLayout();
}

void Panel::setAlpha(f32 a){
	nanogui::Theme *t = panel -> theme();
	nanogui::Color c = t->mWindowPopup;
	t->mWindowPopup = nanogui::Color(c.r(), c.g(), c.b(), a);
}

void Panel::setPosition(Vector2<i32> position) {
    panel -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void Panel::setTooltip(std::string text) {
    panel->setTooltip(text);
}

void Panel::setTitle(std::string t) {
    panel -> setTitle(t);
}

void Panel::setVerticalLayout() {
   panel -> setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 6));
}

void Panel::setGroupLayout() {
    panel -> setLayout(new nanogui::GroupLayout());
}

void Panel::setSize(Vector2<i32> size) {
    panel -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

nanogui::Widget *Panel::getGUIElement() {
    return panel;
}
