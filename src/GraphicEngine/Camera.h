#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>
#include "Vector3.h"

using namespace irr;

class Camera {
    
    public:
        Camera(scene::ISceneManager* sceneManager);
        ~Camera();

        void setPosition(Vector3<float> position);

        void setTargetPosition(Vector3<float> position);

        void setZoom(float zoom);

    private:
        scene::ICameraSceneNode* camera;
};

#endif