#include "Material.h"
#include "Window.h"

using namespace irr;

Material::Material(Texture *tex) { 
    material = new video::SMaterial();
    material->setTexture(0, tex->getTexture());
    material->Lighting = true;
    material->NormalizeNormals = true;
}

Material::~Material() {
    delete material;
}

video::SMaterial * Material::getMaterial() {
    return material;
}