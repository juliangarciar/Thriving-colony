#ifndef TTEXTURE_H
#define TTEXTURE_H

#include <GL/glew.h>

#include "../RETypes.h"

class ResourceIMG;

class TTexture {
    public:
        TTexture(ResourceIMG *);
        ~TTexture();

        GLuint getTextureID();
        ResourceIMG *getResourceIMG();
    private:
        GLuint textureID;

        ResourceIMG *texture;
};
    
#endif