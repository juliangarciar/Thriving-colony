#include "Texture.h"
#include "Screen.h"

using namespace irr;

Texture::Texture(const char* path) {
    texture = Screen::Instance()->getVideoDriver()->getTexture(path);
}

Texture::~Texture() {
    
}

video::ITexture *Texture::getTexture(){
    return texture;
}