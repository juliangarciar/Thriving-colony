#include "SkyDome.h"
#include "Window.h"

SkyDome::SkyDome(Texture* tex) {
	t = tex;
    Window* w = Window::Instance();
    w -> getVideoDriver() -> setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
    skydome = w -> getSceneManager() -> addSkyDomeSceneNode(tex->getTexture(), 16, 8, 0.95f, 2.0f); //ToDo: datos parametrizados
    w -> getVideoDriver() -> setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
}

SkyDome::~SkyDome() {
    //skydome -> remove();
    //skydome -> getParent() -> removeChild(skydome);
    //delete skydome;
    //skydome = nullptr;
	//delete t;
}