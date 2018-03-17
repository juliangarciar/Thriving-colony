#include "ResourceIMG.h"

#include <glm/glm.hpp>

ResourceIMG::ResourceIMG(){

}

ResourceIMG::~ResourceIMG(){
	
}

void ResourceIMG::load(const char *path){
    resource = stbi_load(
        path,
        &width, &height, &channels,
        0
    );
}

void ResourceIMG::release(){
   
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