#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Terrain.h"

using namespace irr;

class Camera {
    
    public:
        Camera(scene::ISceneManager* sceneManager);
        ~Camera();

        void Move(InputManager *receiver, Mouse *cursor, Terrain *terrain);

        void setPosition(Vector3<float> position);

        void setInclination(Vector2<float> inclination);

        void setShadowDistance(float sd);

    private:
        scene::ICameraSceneNode* camera;
        float camSpeed, camHeight, recipsqrt2, tarHeight, Xup, Yup, currentHeight;
        int marginLeft, marginTop, minZoom, maxZoom; //ToDo: Esto no va aqui
        int mapMarginLeft, mapMarginRight, mapMarginTop, mapMarginBottom; //ToDo: Esto no va aqui
        Vector3<float> camPos, camTar1;
        Vector2<float> direction, inclination;
};

#endif