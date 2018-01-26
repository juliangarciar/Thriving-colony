#include "Texture.h"
#include "Window.h"

using namespace irr;

Texture::Texture(const char* path) {
    texture = Window::Instance() -> getVideoDriver() -> getTexture(path);
}

Texture::~Texture() {
    
}

video::ITexture *Texture::getTexture() {
    return texture;
}