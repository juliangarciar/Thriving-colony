#include "Texture.h"
#include "Window.h"

Texture::Texture(const char* path) {
	texture = nullptr;
	if (strchr(path,'.') != NULL) {
		texture = Window::Instance()->getEngine()->createTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE, path);
	}
}

Texture::~Texture() {
    /*if (texture != nullptr) delete texture;
	texture = nullptr;*/
}

OBDTexture *Texture::getTexture() {
    return texture;
}