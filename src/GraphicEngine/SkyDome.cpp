#include "SkyDome.h"

SkyDome::SkyDome(irr::scene::ISceneManager *scene, irr::video::ITexture* tex) {
    skydome=scene->addSkyDomeSceneNode(tex,16,8,0.95f,2.0f);
}

SkyDome::~SkyDome() {
    delete skydome;
}