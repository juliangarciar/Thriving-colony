#include "TLight.h"

TLight::TLight(REColor c, f32 i, bool a) : TEntity(){
    active = a;

    lightType = REEnums::LightTypes::LIGHT_POINT; //ToDo: varios tipos?

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
    if (active) {
        /// esto no sirve pa na porque le vamos a poner la posicion directamente
        // la posicion es un vector 3 hay que meterle la coordenada homogenea antes de pasarselo a opengl y au
        //lightPosition = glm::vec4(0,0,0,1) * modelMatrix;//Posicion a partir de la matriz luz
        //Pasarselo a OpenGL no va aqui no?
    }
}

void TLight::endDraw(){
}
        
void TLight::setAmbientComponent(REColor c, f32 i){
    components.ambientComponent = c.getRGB() * (float)i;
}
        
void TLight::setDiffuseComponent(REColor c, f32 i){
    components.diffuseComponent = c.getRGB() * (float)i;
}
        
void TLight::setSpecularComponent(REColor c, f32 i){
    components.specularComponent = c.getRGB() * (float)i;
}

void TLight::setActive(bool _active) {
    active = _active;
}

bool TLight::getActive() {
    return active;
}

void TLight::setPosition(glm::vec3 p) {
    components.position = p;
}

glm::vec3 TLight::getPosition() {
    return components.position;
}