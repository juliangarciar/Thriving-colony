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

void Mouse::setPosition(Vector2<int> position){
    cursor->setPosition(position.getVectorI());
}

Vector2<int> Mouse::getPosition() {
    return Vector2<int>(cursor->getPosition());
}

gui::ICursorControl *Mouse::getCursor(){
    return cursor;
}