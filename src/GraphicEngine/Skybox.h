#ifndef SKYBOX_H
#define SKYBOX_H

#include "Texture.h"
#include <OBDEngine/OBDSkybox.h>

class Skybox {

    public:
        Skybox(Texture*);
        ~Skybox();
        
    private:
		Texture *t;
        OBDSkybox* skybox;
        
};

#endif