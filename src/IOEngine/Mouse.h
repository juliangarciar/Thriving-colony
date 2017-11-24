#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <irrlicht.h>

using namespace irr;

class Mouse {
    
    public:
        Mouse(scene::ITerrainSceneNode* terrain);
        ~Mouse();
        core::position2d<s32> getPosition();
        void setPositionMouse();

    private:
        scene::ITriangleSelector* selector;;
        gui::ICursorControl *cursor;
        scene::ISceneCollisionManager* collisionManager;
        scene::ISceneNode* sphere;
        core::position2d<s32> pos;
        core::vector3df point;
        core::triangle3df triangle;
        scene::ISceneNode *node;
};

#endif