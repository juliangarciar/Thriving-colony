#include "ResourceIMG.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ResourceIMG::ResourceIMG(){

}

ResourceIMG::~ResourceIMG(){
	
}

void ResourceIMG::load(const char *path){
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

void ResourceIMG::release(){
    stbi_image_free(resource);
}

void ResourceIMG::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceIMG::getIdentifier(){
    return identifier;
}

unsigned char *ResourceIMG::getResource(){
    return resource;
}

int ResourceIMG::getWidth(){ 
    return width;
}

int ResourceIMG::getHeight(){
    return height;
}

int ResourceIMG::getChannels(){
    return channels;
}