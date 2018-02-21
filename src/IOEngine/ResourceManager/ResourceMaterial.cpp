#include "ResourceMaterial.h"

ResourceMaterial::ResourceMaterial(){

}

ResourceMaterial::~ResourceMaterial(){
    
}

void ResourceMaterial::load(const char *path){
    setIdentifier(path);
}

void ResourceMaterial::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceMaterial::getIdentifier(){
    return identifier;
}