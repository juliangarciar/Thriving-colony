#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <Types.h>
#include <MathEngine/Color.h>

class Material {
    public:
        Material(Texture *tex);
        ~Material();
		
        void setColor(Color c);

        //video::SMaterial *getMaterial();
    private:

};

#endif