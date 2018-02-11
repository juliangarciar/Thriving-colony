#ifndef LIGHT_H
#define LIGHT_H

#include <irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>

using namespace irr;

class Light {
    public:
        Light(Vector3<f32> position, f32 intensity);
        ~Light();
    private:
        scene::ILightSceneNode * light;
};

#endif