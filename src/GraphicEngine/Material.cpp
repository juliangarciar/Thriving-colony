#include "Material.h"
#include "Window.h"

using namespace irr;

Material::Material(Texture *tex) { 
    material->setTexture(0, tex->getTexture());
    material->Lighting = true;
    material->NormalizeNormals = true;
}