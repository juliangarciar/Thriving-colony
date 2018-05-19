#include "Material.h"
#include "Window.h"

Material::Material(Texture *tex) {
	//ToDo: textura?
   	material = new OBDMaterial();
    setColor(Color(255, 255, 255));
}

Material::~Material() {
   delete material;
   material = nullptr;
}

void Material::setColor(Color c) {
   material->setDiffuseColor(OBDColor(c.r, c.g, c.b));
}

OBDMaterial *Material::getMaterial() {
    return material;
}