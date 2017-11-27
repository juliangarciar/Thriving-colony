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

        void setPosition(Vector2<int> position);
        
        gui::ICursorControl *getCursor();
        Vector2<int> getPosition();

    private:
        gui::ICursorControl *cursor;
};

#endif