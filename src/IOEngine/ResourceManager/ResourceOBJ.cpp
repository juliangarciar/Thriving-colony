#include "ResourceOBJ.h"

ResourceOBJ::ResourceOBJ(){

}

ResourceOBJ::~ResourceOBJ(){
    
}

void ResourceOBJ::load(const char *path){
    setIdentifier(path);
}

void ResourceOBJ::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceOBJ::getIdentifier(){
    return identifier;
}