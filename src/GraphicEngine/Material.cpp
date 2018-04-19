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
    //material -> remove();
    delete material;
    material = nullptr;
}

video::SMaterial * Material::getMaterial() {
    return material;
}