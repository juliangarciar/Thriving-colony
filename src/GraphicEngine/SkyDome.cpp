#include "SkyDome.h"

SkyDome::SkyDome(irr::scene::ISceneManager *scene, irr::video::ITexture* tex) {
    skydome = scene->addSkyDomeSceneNode(tex, 16, 8, 0.95f, 2.0f); //ToDo: aqui no deberian haber datos
}

SkyDome::~SkyDome() {
    skydome -> remove();
    delete skydome;
    skydome = nullptr;
}