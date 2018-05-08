#ifndef TEXTURE_H
#define TEXTURE_H

#include <Types.h>
#include <OBDEngine/OBDTexture.h>

class Texture {

    public:
        Texture(const char *path);
        ~Texture();
        
        OBDTexture *getTexture();
        
    private:
		OBDTexture *texture;
};

#endif