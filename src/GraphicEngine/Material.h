#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <Types.h>

class Material {
    public:
        Material(Texture *tex);
        ~Material();
		
        void setColor(f32 a, f32 r, f32 g, f32 b);

        //video::SMaterial *getMaterial();
    private:

};

#endif