#ifndef MATERIAL_H
#define MATERIAL_H

#include <irrlicht/irrlicht.h>
#include "Texture.h"
#include <Types.h>

using namespace irr;

class Material {
    public:
        Material(Texture *tex);
        ~Material();

        video::SMaterial *getMaterial();
        void setColor(f32 a, f32 r, f32 g, f32 b);
    private:
        video::SMaterial *material;
};

#endif