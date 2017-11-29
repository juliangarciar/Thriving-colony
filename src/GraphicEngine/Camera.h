#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>
#include "Vector3.h"

using namespace irr;

class Camera {
    
    public:
        Camera();
        ~Camera();

        void setCameraPosition(Vector3<float> position);
        void setTargetPosition(Vector3<float> position);

        //void setCameraRotation(Vector3<float> rotation);

        void setShadowDistance(float sd);

        Vector3<float> getCameraPosition();
        Vector3<float> getTargetPosition();

        //ToDo: no se donde meter esto
        float getReciprocalSquareroot() {
            return core::reciprocal_squareroot((f32)2);
        }
    private:
        scene::ICameraSceneNode* camera;
};

#endif