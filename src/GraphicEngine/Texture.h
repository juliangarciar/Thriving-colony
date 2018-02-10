#ifndef TEXTURE_H
#define TEXTURE_H

#include <irrlicht.h>
#include <Types.h>

using namespace irr;

class Texture {

    public:
        Texture(const char *path);
        ~Texture();
        
        video::ITexture *getTexture();
        
    private:
        video::ITexture *texture;
};

#endif