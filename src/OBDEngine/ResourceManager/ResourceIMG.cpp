#include "ResourceIMG.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ResourceIMG::ResourceIMG() {

}

ResourceIMG::~ResourceIMG() {
	delete resource;
}

void ResourceIMG::load(const char *path) {
    resource = stbi_load(
        path,
        &width, &height, &channels,
        STBI_default
    );
    if (!resource) {
        std::cout << "Failed opening " << path << " image. Check the path." << std::endl;
        exit(0);
    } 
}

void ResourceIMG::release() {
    stbi_image_free(resource);
}

void ResourceIMG::setIdentifier(const char *i) {
    identifier = i;
}

const char *ResourceIMG::getIdentifier() {
    return identifier;
}

unsigned char *ResourceIMG::getResource() {
    return resource;
}

i32 ResourceIMG::getWidth() { 
    return width;
}

i32 ResourceIMG::getHeight() {
    return height;
}

i32 ResourceIMG::getChannels() {
    return channels;
}