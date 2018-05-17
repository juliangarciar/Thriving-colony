#include "TLight.h"

TLight::TLight(OBDColor c, f32 i, f32 am, f32 at) : TEntity(){
    setType(OBDEnums::LightTypes::LIGHT_POINT); //ToDo: varios tipos?

    setColor(c, i);
    setAmbientCoeficient(am);
    setAttenuationCoeficient(at);
    setPosition(glm::vec3(0,0,0));

    active = true;
}

TLight::~TLight(){
}

void TLight::beginDraw(){
    if (active) {
        cache.getLights()->push_back(components);
    }
}

void TLight::endDraw(){
}
        
void TLight::setColor(OBDColor c, f32 i){
	glm::vec3 o = c.getRGB() * (f32)i;
    components.intensity = glm::vec4(o, 1);
}

void TLight::setAmbientCoeficient(f32 c){
	components.ambientCoeficient = c;
}

void TLight::setAttenuationCoeficient(f32 c){
	components.attenuationCoeficient = c;
}

void TLight::setActive(bool a){
    active = a;
}

void TLight::setPosition(glm::vec3 p) {
    components.position = glm::vec4(p, 1);
}

glm::vec3 TLight::getPosition() {
    return components.position;
}

void TLight::setType(OBDEnums::LightTypes newType) {
    components.type = (i32)newType;
}