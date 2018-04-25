#ifndef SKYDOME_H
#define SKYDOME_H

#include "Texture.h"

class SkyDome {

    public:
        SkyDome(Texture*);
        ~SkyDome();
        
    private:
		Texture *t;
        
};

#endif