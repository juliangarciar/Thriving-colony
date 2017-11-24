#include "Mouse.h"
#include "../GraphicEngine/Screen.h"

using namespace irr;

Mouse::Mouse(){
    cursor = Screen::Instance()->getDevice()->getCursorControl();
}

Mouse::~Mouse(){
    delete cursor;
    cursor = NULL;
}

Vector2<float> Mouse::getPosition() {
    return Vector2<float>(cursor->getPosition());
}

gui::ICursorControl *Mouse::getCursor(){
    return cursor;
}