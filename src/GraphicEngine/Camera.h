#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>
#include "Vector3.h"
#include <Types.h>

using namespace irr;

class Camera {
    
    public:
        Camera();
        ~Camera();

        void setCameraPosition(Vector3<f32> position);
        void setTargetPosition(Vector3<f32> position);

        //void setCameraRotation(Vector3<f32> rotation);

        void setShadowDistance(f32 sd);

        Vector3<f32> getCameraPosition();
        Vector3<f32> getTargetPosition();

        //ToDo: no se donde meter esto
        f32 getReciprocalSquareroot() {
            return core::reciprocal_squareroot((f32)2);
        }
    private:
        scene::ICameraSceneNode* camera;
};

#endif