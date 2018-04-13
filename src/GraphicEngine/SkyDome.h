#ifndef SKYDOME_H
#define SKYDOME_H

#include <irrlicht/irrlicht.h>

class SkyDome {

    public:
        SkyDome(irr::scene::ISceneManager *scene, irr::video::ITexture* tex);
        ~SkyDome();
        
    private:
        irr::scene::ISceneNode* skydome;
};

#endif