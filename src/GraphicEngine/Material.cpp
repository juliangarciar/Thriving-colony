#include "Material.h"
#include "Window.h"

Material::Material(Texture *tex) { 
   
    setColor(255, 255, 255, 255);
}

Material::~Material() {
   
}

void Material::setColor(f32 a, f32 r, f32 g, f32 b) {
   
}

/*video::SMaterial * Material::getMaterial() {
    return material;
}*/