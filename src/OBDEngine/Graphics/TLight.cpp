#include "TLight.h"

TLight::TLight(OBDColor c, f32 i) : TEntity(){
    lightType = OBDEnums::LightTypes::LIGHT_POINT; //ToDo: varios tipos?

    setAmbientComponent(c, i);
    setDiffuseComponent(c, i);
    setSpecularComponent(c, i);
    setPosition(glm::vec3(0,0,0));

    cache.getLights()->push_back(components);
    //ToDo: actualizar array de luces cuando se modifica algun parametro (o usar punteros?)
}

TLight::~TLight(){
}

void TLight::beginDraw(){
}

void TLight::endDraw(){
}
        
void TLight::setAmbientComponent(OBDColor c, f32 i){
    components.ambientComponent = c.getRGB() * (float)i;
}
        
void TLight::setDiffuseComponent(OBDColor c, f32 i){
    components.diffuseComponent = c.getRGB() * (float)i;
}
        
void TLight::setSpecularComponent(OBDColor c, f32 i){
    components.specularComponent = c.getRGB() * (float)i;
}

void TLight::setPosition(glm::vec3 p) {
    components.position = p;
}

glm::vec3 TLight::getPosition() {
    return components.position;
}