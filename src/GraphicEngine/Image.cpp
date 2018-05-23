#include "Image.h"
#include "Window.h"

Image::Image(std::string path, Vector3<f32> pos) {
	i = Window::Instance() -> getEngine() -> createImage(
		Window::Instance()->getImageLayer(), 
		Window::Instance()->getImageProgram(), 
		path
	);
	i->setPosition(glm::vec3(pos.x, pos.y, pos.z));
}

Image::~Image() {
    delete i;
	i = nullptr;
}

void Image::setPosition(Vector3<f32> pos) {
	i->setPosition(glm::vec3(pos.x, pos.y, pos.z));
}

void Image::setActive(bool t) {
	i -> setActive(t);
}