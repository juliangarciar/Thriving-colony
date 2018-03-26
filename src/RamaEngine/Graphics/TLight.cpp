#include "TLight.h"

TLight::TLight(REColor c, u32 i, bool a) : TEntity(){
    color = c;
    intensity = i;
    active = a;
    lightPosition = glm::vec3(0,0,0);
    lightType = REEnums::LightTypes::LIGHT_POINT;

    Light l;
    l.color = glm::vec3(color.r, color.g, color.b);
    l.shininess = i;
    cache.getLights()->push_back(l);
    //ToDo: actualizar array de luces cuando se modifica algun parametro (o usa punteros?)
}

TLight::~TLight(){

}

void TLight::beginDraw(){
    if (active) {
        /// esto no sirve pa na porque le vamos a poner la posicion directamente
        // la posicion es un vector 3 hay que meterle la coordenada homogenea antes de pasarselo a opengl y au
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

void TLight::setPosition(glm::vec3 p) {
    lightPosition = p;
}

glm::vec3 TLight::getPosition() {
    return lightPosition;
}