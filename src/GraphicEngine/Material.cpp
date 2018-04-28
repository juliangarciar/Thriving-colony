#include "Material.h"
#include "Window.h"

using namespace irr;

Material::Material(Texture *tex) { 
    material = new video::SMaterial();
    material->setTexture(0, tex->getTexture());
    material->Lighting = true;
    material->NormalizeNormals = true;
    setColor(255, 255, 255, 255);
}

Material::~Material() {
    //material -> remove();
    delete material;
    material = nullptr;
}

video::SMaterial * Material::getMaterial() {
    return material;
}

void Material::setColor(f32 a, f32 r, f32 g, f32 b) {
    material->AmbientColor = video::SColor(a, r, g, b);
    material->DiffuseColor = video::SColor(a, r, g, b);
    material->SpecularColor = video::SColor(a, r, g, b);
    material->EmissiveColor = video::SColor(a, r, g, b);
}