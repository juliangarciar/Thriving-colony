#include "Skybox.h"
#include "Window.h"

Skybox::Skybox(std::vector<std::string> textures) {
	skybox = Window::Instance()->getEngine()->createSkybox(
		Window::Instance()->getSkyboxLayer(), 
		Window::Instance()->getSkyboxProgram(),
		textures
	);
}

Skybox::~Skybox() {
    delete skybox;
	skybox = nullptr;
}