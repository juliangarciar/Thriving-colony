#include "Material.h"
#include "Window.h"

Material::Material(Texture *tex) { 
   
    setColor(Color(255, 255, 255));
}

Material::~Material() {
   
}

void Material::setColor(Color c) {
}

/*video::SMaterial * Material::getMaterial() {
    return material;
}*/