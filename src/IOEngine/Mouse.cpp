#include "Mouse.h"
#include "../GraphicEngine/Window.h"

using namespace irr;

Mouse::Mouse(){
    cursor = Window::Instance()->getDevice()->getCursorControl();
}

Mouse::~Mouse(){
    delete cursor;
    cursor = NULL;
}

void Mouse::show(){
    cursor->setVisible(true);
}

void Mouse::hide(){
    cursor->setVisible(false);
}

void Mouse::changeIcon(gui::ECURSOR_ICON icon){
    if (isVisible()) cursor->setActiveIcon(icon);
}

void Mouse::setPosition(Vector2<int> position){
    cursor->setPosition(position.getVectorI());
}

Vector2<int> Mouse::getPosition() {
    return Vector2<int>(cursor->getPosition());
}

gui::ICursorControl *Mouse::getCursor(){
    return cursor;
}

bool Mouse::isVisible(){
    return cursor->isVisible();
}