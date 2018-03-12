#include "TLight.h"

TLight::TLight(bool a) : TEntity(){
    active = a;
}

TLight::~TLight(){

}

void TLight::beginDraw(){
    if (active) {
        lightPosition = glm::vec4(0,0,0,1) * modelMatrix;//Posicion a partir de la matriz luz
        //Pasarselo a OpenGL no va aqui no?
    }
}

void TLight::endDraw(){

}

void TLight::setIntensity(TColor c){
    intensity = c;
}

TColor TLight::getIntensity(){
    return intensity;
}

void TLight::setActive(bool _active) {
    active = _active;
}

bool TLight::getActive() {
    return active;
}

void TLight::setLightPosition(glm::vec3 p) {
    lightPosition = p;
}

glm::vec3 TLight::getPosition() {
    return lightPosition;
}