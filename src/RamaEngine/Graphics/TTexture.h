#ifndef TTEXTURE_H
#define TTEXTURE_H

#include "../RETypes.h"
#include "../ResourceManager/ResourceBMP.h"

class TTexture {
    public:
        TTexture();
        ~TTexture();

        void setTexture(ResourceBMP *);
        GLuint getTexture();

    private:
        GLuint textureID;
};
    
#endif