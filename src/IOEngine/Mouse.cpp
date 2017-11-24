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

core::position2d<s32> Mouse::getPosition() {
    return cursor->getPosition();
}

gui::ICursorControl *Mouse::getCursor(){
    return cursor;
}