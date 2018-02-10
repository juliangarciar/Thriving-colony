#ifndef LIGHT_H
#define LIGHT_H

#include <irrlicht.h>
#include "Vector3.h"
#include <Types.h>

using namespace irr;

class Light {
    public:
        Light(Vector3<f32> position, f32 intensity);
        ~Light();
    private:
        scene::ILightSceneNode * light;
};

#endif