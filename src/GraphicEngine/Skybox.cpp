#include "Skybox.h"
#include "Window.h"

Skybox::Skybox(Texture* tex) {
	skybox = Window::Instance()->getEngine()->createSkybox(tex->getTexture());
	t = tex;
    
}

Skybox::~Skybox() {
    delete skybox;
	skybox = nullptr;
}