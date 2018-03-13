#include "ResourceIMG.h"

#include <glm/glm.hpp>

ResourceIMG::ResourceIMG(){

}

ResourceIMG::~ResourceIMG(){
	
}

void ResourceIMG::load(const char *path){
    CImg<unsigned char> img(path);
    resource = img.data();
}

void ResourceIMG::release(){
   
}

void ResourceIMG::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceIMG::getIdentifier(){
    return identifier;
}

void *ResourceIMG::getResource(){
    return resource;
}