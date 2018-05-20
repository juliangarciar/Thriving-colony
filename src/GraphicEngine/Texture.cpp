#include "Texture.h"
#include "Window.h"

Texture::Texture(const char* path) {
	if (strchr(path,'.') != NULL) {
		texture = Window::Instance()->getEngine()->createTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE, path);
	}
}

Texture::~Texture() {
    delete texture;
	texture = nullptr;
}

OBDTexture *Texture::getTexture() {
    return texture;
}