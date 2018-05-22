#ifndef SKYBOX_H
#define SKYBOX_H

#include "Texture.h"
#include <OBDEngine/OBDSkybox.h>

class Skybox {

    public:
        Skybox(std::vector<std::string>);
        ~Skybox();
        
    private:
        OBDSkybox* skybox;
        
};

#endif