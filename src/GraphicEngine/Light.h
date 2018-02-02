#ifndef LIGHT_H
#define LIGHT_H

#include <irrlicht.h>
#include "Vector3.h"

using namespace irr;

class Light {
    public:
        Light(Vector3<float> position, float intensity);
        ~Light();
    private:
        scene::ILightSceneNode * light;
};

#endif