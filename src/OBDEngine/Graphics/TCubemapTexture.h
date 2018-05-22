#ifndef TCUBEMAPTEXTURE_H
#define TCUBEMAPTEXTURE_H

#include "../OBDTypes.h"

class ResourceIMG;

class TCubemapTexture {
    public:
        TCubemapTexture(std::vector<ResourceIMG *>);
        ~TCubemapTexture();

        GLuint getTextureID();
    private:
        GLuint textureID;
};
    
#endif