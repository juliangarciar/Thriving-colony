#ifndef TTEXTURE_H
#define TTEXTURE_H

#include "../RETypes.h"
#include "../ResourceManager/ResourceIMG.h"

class TTexture {
    public:
        TTexture();
        ~TTexture();

        void setTexture(ResourceIMG *);
        GLuint getTexture();

    private:
        GLuint textureID;
};
    
#endif