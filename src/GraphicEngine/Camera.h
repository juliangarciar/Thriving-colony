#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>

using namespace irr;

class Camera {
    
    public:
        Camera();
        ~Camera();

        void setCameraPosition(Vector3<f32> position);
        void setTargetPosition(Vector3<f32> position);

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