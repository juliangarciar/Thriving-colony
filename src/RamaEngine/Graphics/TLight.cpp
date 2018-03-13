#include "TLight.h"

TLight::TLight(REColor c, u32 i, bool a) : TEntity(){
    color = c;
    intensity = i;
    active = a;
}

TLight::~TLight(){

}

void TLight::beginDraw(){
    if (active) {
        //lightPosition = glm::vec4(0,0,0,1) * modelMatrix;//Posicion a partir de la matriz luz
        //Pasarselo a OpenGL no va aqui no?
    }
}

void TLight::endDraw(){

}

void TLight::setColor(REColor c){
    color = c;
}

REColor TLight::getColor(){
    return color;
}

void TLight::setIntensity(u32 c){
    intensity = c;
}

u32 TLight::getIntensity(){
    return intensity;
}

void TLight::setActive(bool _active) {
    active = _active;
}

bool TLight::getActive() {
    return active;
}