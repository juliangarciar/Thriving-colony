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

        void show();
        void hide();

        void changeIcon(gui::ECURSOR_ICON icon); //ToDo: arreglar
        
        gui::ICursorControl *getCursor();
        Vector2<int> getPosition();

        bool isVisible();

    private:
        gui::ICursorControl *cursor;
};

#endif