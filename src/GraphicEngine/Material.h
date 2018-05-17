#ifndef MATERIAL_H
#define MATERIAL_H

#include <irrlicht/irrlicht.h>
#include "Texture.h"
#include <MathEngine/Color.h>
#include <Types.h>

using namespace irr;

class Material {
    public:
        Material(Texture *tex);
        ~Material();

        void setColor(Color);

        video::SMaterial *getMaterial();
    private:
        video::SMaterial *material;
};

#endif