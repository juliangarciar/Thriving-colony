#include "TLight.h"

TLight::TLight() : TEntity(){

}

TLight::~TLight(){

}

void TLight::beginDraw(){
    if (active) {
        lightPosition = glm::vec4(0,0,0,1) * modelMatrix;//Posicion a partir de la matriz luz
        //Pasarselo a OpenGL no va aqui?
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

glm::vec4 TLight::getPosition() {
    return lightPosition;
}