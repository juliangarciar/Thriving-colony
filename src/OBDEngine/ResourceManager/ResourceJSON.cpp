#include "ResourceJSON.h"

ResourceJSON::ResourceJSON() {

}

ResourceJSON::~ResourceJSON() {
    
} 

void ResourceJSON::load(const char *path) {
    setIdentifier(path);
    try{
        std::ifstream i;
        i.open(path);
        i >> j;
        i.close();
    }catch(std::ifstream::failure e) {
        std::cerr << "Error: no se pudo abrir el fichero " << path << std::endl;
        exit(0);
    }
}

void ResourceJSON::release() {
    //Release json?
}

void ResourceJSON::setIdentifier(const char *i) {
    identifier = i;
}

const char *ResourceJSON::getIdentifier() {
    return identifier;
}

json *ResourceJSON::getJSON() {
    return &j;
}