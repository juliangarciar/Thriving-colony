#ifndef TEXTURE_H
#define TEXTURE_H

#include <irrlicht.h>

using namespace irr;

class Texture {

    public:
        Texture();
        ~Texture();
        
        video::ITexture *getTexture();
        
    private:
        video::ITexture *texture;
};

#endif