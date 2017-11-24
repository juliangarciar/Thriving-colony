#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>

using namespace irr;

class Mouse {
    
    public:
        Mouse();
        ~Mouse();
        
        gui::ICursorControl *getCursor();
        Vector2<float> getPosition();

    private:
        gui::ICursorControl *cursor;
};

#endif