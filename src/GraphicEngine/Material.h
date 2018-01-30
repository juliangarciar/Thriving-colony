#ifndef MATERIAL_H
#define MATERIAL_H

#include <irrlicht.h>
#include "Texture.h"

using namespace irr;

class Material {
    public:
        Material(Texture *tex);
        ~Material();

        video::SMaterial *getMaterial();
    private:
        video::SMaterial *material;
};

#endif