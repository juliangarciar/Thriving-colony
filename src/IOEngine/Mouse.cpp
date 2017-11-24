#include "Mouse.h"
#include "../GraphicEngine/Screen.h"

using namespace irr;

Mouse::Mouse(scene::ITerrainSceneNode* terrain){
    selector = Screen::Instance()->getSceneManager()->createTerrainTriangleSelector(terrain);
    terrain->setTriangleSelector(selector);
    cursor = Screen::Instance()->getDevice()->getCursorControl();
    collisionManager = Screen::Instance()->getSceneManager()->getSceneCollisionManager();
    sphere = Screen::Instance()->getSceneManager()->addSphereSceneNode();
}

core::position2d<s32> Mouse::getPosition() {
    return pos;
}

void Mouse::setPositionMouse() {
    node = 0;
    const core::line3d<f32> ray = collisionManager->getRayFromScreenCoordinates(pos);
    if (collisionManager->getCollisionPoint (ray, selector, point, triangle, node)) {
        sphere->setPosition(point);
        std::cout << triangle.pointA.X << " " << triangle.pointA.Y << " " << triangle.pointA.Z << std::endl;
    }
}

Mouse::~Mouse(){
    delete selector;
    selector = NULL;
    delete cursor;
    cursor = NULL;
    delete collisionManager;
    collisionManager = NULL;
    delete sphere;
    sphere = NULL;
    delete node;
    node = NULL;
}
