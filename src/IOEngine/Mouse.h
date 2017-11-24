#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <irrlicht.h>

using namespace irr;

class Mouse {
    
    public:
        Mouse();
        ~Mouse();
        
        gui::ICursorControl *getCursor();
        core::position2d<s32> getPosition();

    private:
        gui::ICursorControl *cursor;
};

#endif