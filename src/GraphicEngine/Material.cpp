#include "Material.h"
#include "Window.h"

using namespace irr;

Material::Material(Texture *tex) { 
    material = new video::SMaterial();
    material->setTexture(0, tex->getTexture());
    material->Lighting = true;
    material->NormalizeNormals = true;
    setColor(Color(255, 255, 255, 255));
}

Material::~Material() {
    delete material;
    material = nullptr;
}

void Material::setColor(Color c) {
    material->AmbientColor = video::SColor(c.a, c.r, c.g, c.b);
    material->DiffuseColor = video::SColor(c.a, c.r, c.g, c.b);
    material->SpecularColor = video::SColor(c.a, c.r, c.g, c.b);
    material->EmissiveColor = video::SColor(c.a, c.r, c.g, c.b);
}

video::SMaterial * Material::getMaterial() {
    return material;
}