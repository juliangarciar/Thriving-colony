#ifndef SKYDOME_H
#define SKYDOME_H

#include <irrlicht/irrlicht.h>

#include <GraphicEngine/Texture.h>

class SkyDome {

    public:
        SkyDome(Texture*);
        ~SkyDome();
        
    private:
		Texture *t;
        irr::scene::ISceneNode* skydome;
};

#endif