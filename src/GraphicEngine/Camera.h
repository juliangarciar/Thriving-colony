#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>
#include <IOEngine/Input.h>
#include "Vector2.h"
#include "Vector3.h"

using namespace irr;

class Camera {
    
    public:
        Camera(scene::ISceneManager* sceneManager);
        ~Camera();

        void Move(Input *receiver);

        void setPosition(Vector3<float> position);

        void setTargetPosition(Vector3<float> position);

        void setShadowDistance(float sd);

    private:
        scene::ICameraSceneNode* camera;
        float camSpeed, camHeight, camRadius, recipsqrt2, tarHeight, Xup, Yup, currentHight;
        Vector3<float> camPos, camTar1;
        Vector2<float> direction;
};

#endif