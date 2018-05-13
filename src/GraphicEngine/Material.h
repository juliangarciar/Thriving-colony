#ifndef MATERIAL_H
#define MATERIAL_H

#include <OBDEngine/OBDMaterial.h>

#include "Texture.h"
#include <Types.h>
#include <MathEngine/Color.h>

class Material {
    public:
        Material(Texture *tex);
        ~Material();
		
        void setColor(Color c);

        //OBDMaterial *getMaterial();
    private:

};

#endif